
#include <iostream> 
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using v6 = std::vector<int64_t>;

using namespace std;

int64_t result = 0;
int64_t result2 = 0;

bool isZero(v6 &v) {
    for (auto it=v.begin(); it !=v.end(); it++) {
        if (*it != 0) return false;
    } 
    return true;
}

int64_t solve(vector<v6> &all) {
    do 
    {
        v6 tmp;
        for (int y=0; y<all.back().size()-1; y++) {
            int64_t n = all.back()[y+1] - all.back()[y];
            tmp.push_back(n);
        }
        all.push_back(tmp);

    } while (!isZero(all.back()));

    // backwards
    for (int y=all.size()-1; y>0; y--) {
        int64_t nextNumb =  all[y].back() + all[y-1].back();
        all[y-1].push_back(nextNumb);
    }
    return all[0].back();
}
            
int main()
{
    vector_str file = import_file( "input/d09.txt" );
    for (string line : file) {
        int64_t count = 0;
        vector<string> words = line_to_words(line);
        vector<v6> all; v6 record;
        for (string n : words) record.push_back(convert_to<int>(n));
        all.push_back(record);

        result += solve(all);
    }

    cout << result << endl; 

    return 0;
}