
#include <algorithm>
#include <iostream>
#include <numeric>
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

string directions;
map<string,vector<string>> diz;

int dir;
int ind = 0;
int stepsA = 0;
int stepsB = 0;
map<char,int> dirs = {{'L',0},{'R',1}};

string cur = "AAA";
vector<string> starts;

            
int main()
{
    vector_str file = import_file( "input/d08.txt" );
    directions = file[0];
    for (int i=2; i<file.size(); i++) {
        string line = file[i];
        replace_char(line, '(',' ');
        replace_char(line, '=',' ');
        replace_char(line, ',',' ');
        vector_str tmp = line_to_words(line.substr(0,line.size()-1));
        vector_str possible_ways;
        possible_ways.push_back(tmp[1]);
        possible_ways.push_back(tmp[2]);
        diz[tmp[0]] = possible_ways;

        if (tmp[0][2] == 'A') starts.push_back(tmp[0]);
    }

    while (cur != "ZZZ") 
    {
        char c = directions[ind];
        cur = diz[cur][dirs[c]];

        ind = (ind + 1) % directions.size();
        stepsA++;
    }
    cout << stepsA << "\n\n" << endl;

    //find time for every single start
    vector<int> lcms;
    for (int i=0; i<starts.size(); i++) {
        
        ind = 0; stepsA = 0;
        while (starts[i][2] != 'Z') 
        {
            char c = directions[ind];
            starts[i] = diz[starts[i]][dirs[c]];

            ind = (ind + 1) % directions.size();
            stepsA++;
        }
        lcms.push_back(stepsA);
    }

    show_content(lcms);

    return 0;
}

/*
Python:
from math import lcm
numbers = [
            16579,
            18827,
            19951,
            12083,
            22199,
            17141
            ]
print(lcm(*lcms))

*/