#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <mutex>
#include <any>
#include <set>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using Anyset = std::map<std::string, std::map<std::string, std::any>>;
using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

using namespace std;

// template <typename R, typename... A>
// class CacheDecorator {
//     public:
//     CacheDecorator(std::function<R(A...)> f) : f_(f) {}

//     R operator()(A... a) {
//         std::tuple<A...> key(a...);
//         auto search = map_.find(key);
//         if (search != map_.end()) {
//             return search->second;
//         }

//         auto result = f_(a...);
//         map_[key] = result;
//         return result;
//     }

//     private:
//     std::function<R(A...)> f_;
//     std::map<std::tuple<A...>, R> map_;
// };

// template <typename R, typename... Args>
// std::function<R (Args...)> memo(R (*fn)(Args...)) {
//     std::map<std::tuple<Args...>, R> table;
//     return [fn, table](Args... args) mutable -> R {
//         auto argt = std::make_tuple(args...);
//         auto memoized = table.find(argt);
//         if(memoized == table.end()) {
//             auto result = fn(args...);
//             table[argt] = result;
//             return result;
//         } else {
//             return memoized->second;
//         }
//     };
// }

// #define MEMOIZATOR(N, R, ...)                               \
// R _ ## N (__VA_ARGS__);                                     \
// std::map<std::tuple<__VA_ARGS__>, R> _memo_ ## N;           \
// template <typename ... Args>                                \
// R N (Args ... args) {                                       \
//     auto& _memo = _memo_ ## N;                              \
//     auto result = _memo.find(std::make_tuple(args...));     \
//     if (result != _memo.end()) {                            \
//         return result->second;                              \
//     }                                                       \
//     else {                                                  \
//         auto result = _ ## N  (args...);                    \
//         _memo[std::make_tuple(args...)] = result;           \
//         return result;                                      \
//     }                                                       \
// }                                                           \

template<typename Function, typename... Args>
auto invoke_memoized(Function function, Args... args)
{
    using key_type   = std::tuple<Args...>;
    using value_type = std::invoke_result_t<Function, Args...>;

    static_assert(! std::is_same_v<Function, std::function<value_type(Args...)>>,
        "cannot memoize on std::function (use a lambda instead)");

    static_assert(! std::is_same_v<Function, value_type(*)(Args...)>,
        "cannot memoize on function pointer (use a lambda instead)");

    static std::mutex mutex;
    static std::map<key_type, value_type> cache;

    auto key  = std::tuple(args...);
    auto lock = std::lock_guard<std::mutex>(mutex);

    if (cache.count(key))
    {
        return cache[key];
    }
    return cache[key] = std::apply(function, key);
}

bool is_open(string v, set<string> valves) {
    return valves.find(v) != valves.end();
}

// MEMOIZATOR(part_one, int, set<string>, int, string, Anyset&);
int part_one(set<string> opened, int minutes, string cur_valve, map<string, vector_str> all_valves, map<string, int> all_pressures) 
{
    if (minutes <= 0) return 0;
    
    int best = 0;

    for (string new_valve : all_valves[cur_valve]) {
        //cout << "diobono "<< best << endl;
        best = max<int>(best, part_one(opened, minutes - 1, new_valve, all_valves, all_pressures));
    }
    if (!is_open(cur_valve, opened) && 
            (all_pressures[cur_valve] > 0) && 
                (minutes > 0)) 
        {
            set<string> new_opened = opened;
            new_opened.insert(cur_valve);
            set<string> final_opened = new_opened;

            minutes -= 1;
            int new_best = minutes * all_pressures[cur_valve];

            for (string upd_valve : all_valves[cur_valve]) {
                best = max<int>(best, new_best + part_one(final_opened, minutes - 1, upd_valve, all_valves, all_pressures));
            }
        }
    return best;
}

int somma(int a, int b) { return a + b;};

int main()
{
    vector_str file = import_file("input/d16.txt");
    
    Anyset state;
    map<string, vector_str> all_valves;
    map<string, int> all_pressures;

    for (string line : file) 
    {
        vector_str vals;
        vector_str words = line_to_words(line);
        vector_str valv_to_parse = slice_vector(9, words.size(), words);
        
        string name = words[1];
        int rate = convert_to<int>(words[4].substr(5, words[4].find(';') - 5));
        for (string v : valv_to_parse) 
            vals.push_back(v.substr(0, 2));

        // state[name]["rate"] = rate;
        // state[name]["valves"] = vals;
        all_valves[name] = vals;
        all_pressures[name] = rate;
    }
    
    const set<string> opened;
    //CacheDecorator<int, set<string>, int, string, Anyset&> p_o(part_one);
    
    //cout<<part_one(opened, 30, "AA", state);
    
    cout << part_one(opened, 30, "AA", all_valves, all_pressures);
    auto c = invoke_memoized(part_one, opened, 30, "AA", all_valves, all_pressures);

    return 0;
}
