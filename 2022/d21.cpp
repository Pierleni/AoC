#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

using namespace std;

// Operational functions
uint64_t add(uint64_t &a, uint64_t &b) {return a + b;}
uint64_t sub(uint64_t &a, uint64_t &b) {return a - b;}
uint64_t mul(uint64_t &a, uint64_t &b) {return a * b;}
uint64_t div(uint64_t &a, uint64_t &b) {return a / b;}

// Map for operations
map<string, uint64_t(*)(uint64_t&,uint64_t&)> operation = {
    {"+", &add}, {"-", &sub},
    {"*", &mul}, {"/", &div}
};

map<string, uint64_t> monkeys;
vector<pair<string, vector<string>>> data_or;

uint64_t solve_part1() 
{
    while (monkeys.count("root") == 0) 
    {
        for (auto &d : data_or) {
            if (monkeys.count(d.first)) continue;
            string a    = d.second[0];
            string op   = d.second[1];
            string b    = d.second[2];
            
            if (monkeys.count(a) && monkeys.count(b)) {
                monkeys[d.first] = operation[op](monkeys[a], monkeys[b]);
            }
        }
    }
    return monkeys["root"];
}

int main()
{
    vector_str file = import_file("input/d21.txt");
    for (string &line : file)
    {
        replace(line.begin(), line.end(),':', ' '); // replace ':'
        vector_str split = line_to_words(line);  
        pair<string, vector<string>> pair_temp;     // temporary pair
        pair_temp.first = split[0];                 // first element
        for (int i=1; i<split.size(); i++) {
            pair_temp.second.push_back(split[i]);   // second element
        }
        data_or.push_back(pair_temp);
    }

    for (auto &d : data_or) {
        if (d.second.size() > 1) continue; 
        uint64_t value = convert_to<uint64_t>(d.second[0]);
        monkeys[d.first] = value;
    }

    cout << solve_part1();

    return 0;
}
