#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#include "../libcpp/io.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;


int find_duplicates(std::string line, std::set<char> container) 
{
    int priority;
    char duplicate;

    for (char c : line) {
        auto pos = container.find(c);
        if (pos != container.end()) duplicate = c;
    }

    if (islower(duplicate)) return (int) duplicate - 96;
    else return (int) duplicate - 38;
}


int main()
{
    vector_str file = import_file("input/d03.txt");
    
    std::string first, second, third;
    
    int sum_part_1 = 0;
    int sum_part_2 = 0;
    
    // Part 1
    for (size_t i = 0; i < file.size(); i++)
    {
        first = file[i].substr(0, (file[i].size() / 2));
        second = file[i].substr((file[i].size() / 2));

        std::set<char> container;
        
        for (char c : first) {
            container.insert(c);
        }
        sum_part_1 += find_duplicates(second, container);
    }
    std::cout << "Part 1: " << sum_part_1 << std::endl;

    // Part 2
    for (size_t i = 0; i < file.size(); i += 3)
    {
        first = file[i];
        second = file[i+1];
        third = file[i+2];

        std::set<char> container;
        std::set<char> container_2;

        for (char c : first) {
            container.insert(c);
        }
        for (char c : second) {
            auto pos = container.find(c);
            if (pos != container.end()) container_2.insert(c);
        }
        
        sum_part_2 += find_duplicates(third, container_2);
    }
    std::cout << "Part 2: " << sum_part_2;

    return 0;
}