#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

#include <map>


int main()
{
    vector_str file = import_file("input/d01.txt");
    std::vector<int> charts;
    int checkSum = 0;

    for (size_t i = 0; i <= file.size(); i++)
    {
        std::string line = file[i];

        if (line != "") {
            checkSum += convert_to<int>(line);
        }
        else {
            charts.push_back(checkSum);
            checkSum = 0;
        }
    }

    std::sort(charts.rbegin(), charts.rend());

    int part1_result = charts[0];
    int part2_result = charts[0] + charts[1] + charts[2];
    std::cout << "Part 1: " << part1_result << std::endl;
    std::cout << "Part 2: " << part2_result << std::endl;

    return 0;
}
