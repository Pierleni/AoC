
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using namespace std;

using Lens = tuple<string,int>;
using Box = vector<Lens>;
using BoxList = vector<Box>;
            
int main()
{
    BoxList B;
    int64_t resultA = 0;
    int64_t resultB = 0;

    B.resize(256);

    std::vector<std::string> file = import_file( "input/d15.txt" );
    replace(file[0].begin(), file[0].end(),',',' ');
    std::vector<string> seques = line_to_words(file[0]);

    /////////////// P A R T 1
    for (string s : seques) {
        int64_t value = 0;
        for (char c : s) {
            value += (int)c;
            value *= 17;
            value %= 256;   
        }    
        resultA += value;
    }
    cout << resultA << endl;

    //////////////// P A R T 2

    for (string s : seques) {
        int64_t v = 0;
        string label;
        int i = 0;
        for (; i<s.size(); i++) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') {
                label += c;
                v += (int)c;
                v *= 17;
                v %= 256;   
            }
            if (c == '-') {
                auto it = std::find_if(B[v].begin(), B[v].end(), [label](const std::tuple<string,int>& e) {return std::get<0>(e) == label;});
                if (it != B[v].end()) {
                    B[v].erase(it);

                }
            }
            if (c == '=') {
                int focal_length = s[i+1] - '0';
                Lens lens = {label, focal_length};
                auto it = std::find_if(B[v].begin(), B[v].end(), [label](const std::tuple<string,int>& e) {return std::get<0>(e) == label;});
                if (it != B[v].end()) {
                    *it = lens;
                    // B[v].erase(it);
                    // B[v].insert(it, make_tuple(label, (int)s[i+1] - '0'));
                } 
                else {
                    B[v].push_back(lens);
                } 
            }
        }
    }

    for (int box=0; box<256; box++) {
        for (int pos=0; pos<B[box].size(); pos++) {
            resultB += ((box+1) * (pos+1)) * get<1>(B[box][pos]);
        }
    }
    cout << resultB;
    return 0;
}