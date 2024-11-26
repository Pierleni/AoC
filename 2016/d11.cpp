#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>

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

#include <map>

int main()
{
    vector_str file = import_file("input/d11.txt");
    vector<vector<string>> all_words;
    vector<vector<int>> floors;
    vector<string> Elements;
    for (string &lines : file) {
        replace_char(lines, '-', ' ');
        replace_char(lines, ',', ' ');
        vector_str words = line_to_words(lines);
        all_words.push_back(words);
    }

    for (vector<string> line : all_words) {
        vector_int floor;
        floors.push_back(floor);
        for (int i=0; i<line.size(); i++) {
            //cout << i << ' ' << line[i] << endl;
            if ((line[i] == "compatible") || (line[i] == "generator") || (line[i] == "generator.")) {
                if (find(Elements.begin(), Elements.end(), line[i-1]) == Elements.end())
                    Elements.push_back(line[i-1]);
                vector<string>::iterator it = find(Elements.begin(), Elements.end(), line[i-1]);
                int index = it - Elements.begin();
                floors.back().push_back((1 + index) * (line[i] == "generator" || line[i] == "generator." ? 1 : -1));
            }
        }
    }
    show_matrix(floors);
    
    //regex word_regex("(\w+)(?:-compatible)? (microchip|generator)");
    
    
  

    return 0;
}
