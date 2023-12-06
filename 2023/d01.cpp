
#include <iostream>
#include <vector>
#include <string_view>
#include <regex>
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

map<string, char> diz = {{"one",'1'},{"two",'2'},{"three",'3'},{"four",'4'},{"five",'5'},{"six",'6'},{"seven",'7'},{"eight",'8'},{"nine",'9'}};

int64_t result1 = 0;
int64_t result2 = 0;
            
int main()
{
    vector_str file = import_file( "input/d01.txt" );
    for (string line : file)
    {
        string number = "";
        for (int i=0; i<line.size(); i++) {
            if (isdigit(line[i])) {
                number += line[i];
                break;
            }
        }
        for (int i=line.size()-1; i>=0; i--) {
            if (isdigit(line[i])) {
                number += line[i];
                break;
            }
        }
        result1 += convert_to<int>(number);
    }

    cout << result1 << endl;

    for (string line : file)
    {
        vector<char> digit;
        string numbera = "";
        
        for (int i=0; i<line.size(); i++) {
            if (isdigit(line[i])) digit.push_back(line[i]);
            for (auto w : diz) {
                if (line.substr(i,w.first.length()) == w.first) {
                    digit.push_back(w.second);
                }
            }
        }
        numbera += digit[0];
        numbera += digit[digit.size()-1];
    }

    cout << result2 << endl; //53363 no

    return 0;
}