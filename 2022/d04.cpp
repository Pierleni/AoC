#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;

#include <map>

int main()
{
    vector_str file = import_file("input/d04.txt");
    int contained = 0;
    int overlap = 0;
    
    for (std::string lines : file) {
        replace_char(lines, ',', ' ');
        replace_char(lines, '-', ' ');
        vector_str line = line_to_words(lines);

        int minA = convert_to<int>(line[0]); 
        int maxA = convert_to<int>(line[1]);  
        int minB = convert_to<int>(line[2]);  
        int maxB = convert_to<int>(line[3]); 

        if ((minB >= minA && maxB <= maxA) || 
            (minA >= minB && maxA <= maxB)) contained++;

        if ((minB <= maxA && maxB >= minA) ||
            (minA <= maxB && maxA >= minB)) overlap++;
    }
    std::cout << "Part 1: " << contained << std::endl;
    std::cout << "Part 2: " << overlap;

    return 0;
}
