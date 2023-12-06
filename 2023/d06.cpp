
#include <iostream>
#include <vector>
#include <chrono>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

using namespace std;
using namespace std::chrono;

vector<uint64_t> Time;
vector<uint64_t> Distance;

vector<uint64_t> singleRace;
vector<uint64_t> singleT;
vector<uint64_t> singleD;

uint64_t solve(vector<uint64_t> &Time, vector<uint64_t> &Distance) {
    uint64_t result = 1;
    for (uint64_t i=0; i<Time.size(); i++) {
        uint64_t count = 0;
        for (uint64_t p=0; p<=Time[i]; p++) {
            if (p * (Time[i]-p) > Distance[i]) {
                count++;
            }
        }
        result *= count;
    }
    return result;
}
            
int main()
{
    auto start = high_resolution_clock::now();
    vector_str file = import_file( "input/d06.txt" );
    for (int y=0; y<2; y++) {
        vector_str line = line_to_words(file[y]);
        string digit = "";
        for (int x=0; x<line.size(); x++) {
            if (x != 0) {
                digit += line[x];
                if (y == 0) Time.push_back(convert_to<int>(line[x]));
                else Distance.push_back(convert_to<int>(line[x]));
            }
        }
        singleRace.push_back(convert_to<uint64_t>(digit));
    }
    singleT.push_back(singleRace[0]);
    singleD.push_back(singleRace[1]);

    
    cout << "Part 1: " << solve(Time,Distance) << endl;
    cout << "Part 2: " << solve(singleT,singleD) << endl;

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << duration.count() << endl;

    return 0;
}