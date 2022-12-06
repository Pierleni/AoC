#include <iostream>
#include <vector>
#include <deque>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_char = std::vector<char>;


int main()
{
    vector_str file = import_file("input/d05.txt");
    std::vector<std::deque<char>> allRacks;
    std::vector<std::deque<char>> allRacks_v2;
    // fill all Racks
    for (size_t i = 0; i < 9; i++) {   
        std::deque<char> deq;
        allRacks.push_back(deq);
        allRacks_v2.push_back(deq);
    }
    // feed single rack
    for (int i=0; i<8; i++) {           
        std::string line = file[i];
        replace_char(line, ' ', 'x');

        int column = 0;
        for (size_t j = 0; j < line.size(); j += 4)
        {
            if (line[j + 1] != 'x') {
                allRacks[column].push_back(line[j + 1]);    // for part 1
                allRacks_v2[column].push_back(line[j + 1]); // for part 2 (copy)
            }
            column++;
        }
    }

    std::string part_1 = "";
    std::string part_2 = "";

    for ( int i = 10; i < file.size(); i++)     
    {
        vector_str line = line_to_words(file[i]);
        int move = convert_to<int>(line[1]);
        int from = convert_to<int>(line[3]);
        int dest = convert_to<int>(line[5]);

        // Part 1
        for (size_t k = 0; k < move; k++)
        {
            char a = allRacks[from - 1][0];                 // save char
            allRacks[from - 1].pop_front();                 // pop
            allRacks[dest - 1].push_front(a);               // push it
        }

        // Part 2
        std::string tempChars = "";
        for (size_t k2 = 0; k2 < move; k2++) 
        {
            tempChars += allRacks_v2[from - 1][0];          // create str
            allRacks_v2[from - 1].pop_front();              // pop chars 
        }
        for (int f = move - 1; f > -1; --f) {              
            allRacks_v2[dest - 1].push_front(tempChars[f]); // push in reverse
        }
    }
    // Print both parts solution
    for (auto rack : allRacks) {
        part_1 += rack[0];
    }
    for (auto rack : allRacks_v2) {
        part_2 += rack[0];
    }

    std::cout << "Part 1: " << part_1 << std::endl;
    std::cout << "Part 2: " << part_2;

    return 0;
}