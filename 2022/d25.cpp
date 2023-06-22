#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;

std::map<char,int> diz = {{'0',0},{'1',1},{'2',2},{'=',-2},{'-',-1}};
std::map<int64_t,char> rev = {{0,'0'},{1,'1'},{2,'2'},{-2,'='},{-1,'-'}};


int main()
{
    vector_str file = import_file("input/d25.txt");
    
    // find decimal
    std::string snafu = "";
    int64_t decimal = 0;
    for (std::string line : file) {
        int64_t digit = 0;
        int length = line.size() - 1;
        for (int i=0; i<=length; i++) {
            digit += pow(5, length - i) * diz[line[i]];
        }
        decimal += digit;
    }

    // find snafu
    while (decimal > 0) {
        int64_t value = decimal % 5;
        if (value >= 3) value -= 5;
        snafu += rev[value];
        decimal -= value;
        decimal /= 5;       
    }
    std::reverse(snafu.begin(), snafu.end());
    std::cout << "Part 1: " << snafu;

    return 0;
}