#include <unordered_map>
#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
#include <map>
#include <set>

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

int get_value(vector<pair<int,int>> &cur)
{
    int sum = 0;
    for (pair<int,int> &t : cur) {
        sum += t.first + t.second;
    }
    return sum;
}

pair<int,int> bfs(unordered_map<int, set<int>> &components)
{
    deque<vector<pair<int,int>>> que;
    int best, best2, maxL;
    for (auto c : components[0]) {
        vector<pair<int,int>> v;
        v.push_back({0, c});
        que.push_back(v);
    }
    while (!que.empty())
    {
        vector<pair<int,int>> cur = que.front();
        int b = cur[cur.size()-1].second;
        que.pop_front();
        best = max(best, get_value(cur));
        for (auto &x : components[b]) {
            pair<int,int> normal = make_pair(b, x);
            pair<int,int> reverse = make_pair(x, b);
            if (find(cur.begin(), cur.end(), normal) == cur.end() &&
                find(cur.begin(), cur.end(), reverse) == cur.end()) 
                {
                    vector<pair<int,int>> tmp = cur;
                    tmp.push_back(normal);
                    que.push_back(tmp);
                }

            // part 2
            if (cur.size() >= maxL) {
                if (cur.size() != maxL) {
                    maxL = cur.size();
                    best2 = 0;
                }
                best2 = max(best2, get_value(cur));
            }
        }
    }

    return {best,best2};
}

int main()
{
    vector_str file = import_file("input/d24.txt");
    unordered_map<int, set<int>> components;
    components.reserve(1000);
    for (string line : file) {
        int a, b;
        replace(line.begin(), line.end(), '/', ' ');
        vector_str words = line_to_words(line);
        components[convert_to<int>(words[0])].insert(convert_to<int>(words[1]));
        components[convert_to<int>(words[1])].insert(convert_to<int>(words[0]));
    }

    pair<int,int> solution = bfs(components);
    cout << solution.first << endl;
    cout << solution.second << endl;

    return 0;
}
