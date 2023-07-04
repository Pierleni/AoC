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
vector<pair<string, vector<string>>> data_rev;


uint64_t straight(string reference, vector<pair<string, vector<string>>> &data, map<string, uint64_t> &monky) 
{
    while (monky.count(reference) == 0) 
    {
        for (auto &d : data) {
            if (monky.count(d.first)) continue;
            string a    = d.second[0];
            string op   = d.second[1];
            string b    = d.second[2];
            
            if (monky.count(a) && monky.count(b)) {
                monky[d.first] = operation[op](monky[a], monky[b]);
            }
        }
    }
    return monky[reference];
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

    string root_a, root_b;

    for (auto &d : data_or) {
        if (d.first == "root") {
            root_a = d.second[0];
            root_b = d.second[2];
        }
        if (d.first == "humn" || d.second.size() > 1) continue;
        uint64_t value = convert_to<uint64_t>(d.second[0]);
        monkeys[d.first] = value;
    }

    // erase root and humn
    for (int i=0; i<data_or.size(); i++) {
        if (data_or[i].first == "root" || data_or[i].first == "humn") {
            data_or.erase(data_or.begin() + i);
        }
    }
    
    // find root_b to get root_a too
    uint64_t node = straight(root_b, data_or, monkeys);
    monkeys[root_b] = node;
    monkeys[root_a] = node;

    // reverse data
    for (auto &d : data_or) 
    {
        string a, b1, b2, op, x1, x2;
        if (d.second.size() > 1) 
        {
            a = d.first;
            x1 = d.second[0]; b1 = d.second[0];
            op = d.second[1];
            b2 = d.second[2]; x2 = d.second[2];
            
            pair<string, vector_str> tmp1;
            pair<string, vector_str> tmp2;
            
            switch ((char)op[0])
            {
                case '*':
                    tmp1 = {x1, {a, "/", b2}};
                    tmp2 = {x2, {a, "/", b1}};
                    break;

                case '+': 
                    tmp1 = {x1, {a, "-", b2}};
                    tmp2 = {x2, {a, "-", b1}};
                    break;

                case '-': 
                    tmp1 = {x1, {a, "+", b2}};
                    tmp2 = {x2, {b1, "-", a}};
                    break;

                case '/': 
                    tmp1 = {x1, {a, "*", b2}};
                    tmp2 = {x2, {b1, "/", a}};
                    break;
            
            }

            data_rev.push_back(tmp1);
            data_rev.push_back(tmp2);
        }
    }

    cout << "Part 2: " << straight("humn", data_rev, monkeys); // 3469704905529

    return 0;
}
