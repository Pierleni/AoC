
#include <iostream>
#include <vector>
#include <string>
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
map<string, int> bid;
//char cards[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
map<char,int> cards = {
    {'2',0},{'3',1},{'4',2},{'5',3},{'6',4},{'7',5},{'8',6},{'9',7},{'T',8},
    {'J',9},{'Q',10},{'K',11},{'A',12}};

vector_str fives;
vector_str fours;
vector_str fulls;
vector_str three;
vector_str two_p;
vector_str one_p;
vector_str zeros;
vector<vector<string>> all_cases;

set<char> getSet(string &s) {
    set<char> tmp;
    for (char c : s) {tmp.insert(c);}
    return tmp;
}

bool cmp(const pair<char, int> &a, const pair<char,int> &b) {
    return a.second < b.second;
}

void two_tre(string &s, int rep, int value){
    int higher = 0;
    map<char, int> counter;
    vector<pair<char, int>> sortVec;
    string newDigit = "";
    for (int i=0; i<s.size(); i++) {
        counter[s[i]] = 1;
        for (int j=0; j<s.size(); j++) {
            if (i != j) {
                if (s[i] == s[j]) counter[s[i]]++;
            }
        }
    }
    //sort(counter.begin(), counter.end(), cmp);
    for (auto c : counter) {
        sortVec.push_back({c.first, c.second});
    }
    sort(sortVec.begin(), sortVec.end(),cmp);
    for (auto c : sortVec) {
        if (c.second > higher) higher = c.second;
        newDigit += std::string(c.second,c.first);

    }
    if (rep == 5){
        zeros.push_back(newDigit);
    }
    if (rep == 4){
        one_p.push_back(newDigit);
    }
    if (rep == 3){
        if (higher == 3) three.push_back(newDigit);
        if (higher == 2) two_p.push_back(newDigit);
    }
    if (rep == 2){
        if (higher == 3) fulls.push_back(newDigit);
        if (higher == 4) fours.push_back(newDigit);
    }
    if (rep == 1){
        fives.push_back(newDigit);
    }
    bid[newDigit] = value;
    
}

            
int main()
{
    vector_str file = import_file( "input/d07.txt" );
    for (string f : file) {
        vector_str line = parse_line_byChar(f, ' ');
        // populate bid
        //sort(line[0].begin(), line[0].end(),[](char &a, char &b){return cards[a] < cards[b];});
        //bid[line[0]] = convert_to<int>(line[1]);

        if (getSet(line[0]).size() == 5) two_tre(line[0], 5, convert_to<int>(line[1]));
        if (getSet(line[0]).size() == 4) two_tre(line[0], 4, convert_to<int>(line[1]));
        if (getSet(line[0]).size() == 3) two_tre(line[0], 3, convert_to<int>(line[1]));
        if (getSet(line[0]).size() == 2) two_tre(line[0], 2, convert_to<int>(line[1]));
        if (getSet(line[0]).size() == 1) two_tre(line[0], 1, convert_to<int>(line[1]));
    }
    all_cases = {zeros,one_p,two_p,three,fulls,fours,fives};
    for (auto &group : all_cases) {
        sort(group.rbegin(), group.rend());
    }
    for (auto v : all_cases) {
        for (auto c : v) {
            cout << c << ' ';
        }
        cout << endl;
    }

    uint64_t result = 0;
    int count = 1;
    for (auto &group : all_cases) {
        for (auto card : group) {
            cout << card << ' ' << bid[card] << ' ' << count << endl;
            result += bid[card] * count;
            count++;
        }
    }
    cout << result;

    return 0;
}