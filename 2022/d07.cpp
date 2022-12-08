#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

#include <map>

#define DISK_SPACE 70000000
#define REQUIRED_SPACE 30000000

int main()
{
    vector_str file = import_file("input/d07.txt");
    std::map<std::string, int> directories_size;
    vector_str folders;

    for (std::string command : file) 
    {
        vector_str line = line_to_words(command);
        
        if (line[1] == "cd") {
            if (line[2] == "..") folders.pop_back();
            else folders.push_back(line[2]);
        }

        else if ((line[0] != "$") && (line[0] != "dir")) 
        {
            int size = convert_to<int>(line[0]);
            std::string path = "";
            
            for (int i = 0; i < folders.size() +1; i++) {
            for (int j = 0; j < i; j++) path += folders[j];

                if (directories_size.empty()) directories_size[path] = size;
                else {
                    if (directories_size.find(path) == directories_size.end())
                        directories_size[path] = size;
                    else 
                        directories_size[path] += size;
                }
            }       
        }
        else if (line[1] == "ls") 
            continue;
    }
    // Part 1  
    int part_1 = 0;
    for (auto d : directories_size) {
        if (d.second <= 100000) part_1 += d.second;
    }
    // Part 2
    int difference = DISK_SPACE - directories_size[""];
    vector_int possible_folders;
    for (auto d : directories_size) {
        if ((difference + d.second) >= REQUIRED_SPACE) {
            possible_folders.push_back(d.second);
        }
    }
    std::cout << "Part 1: " << part_1 << std::endl;
    std::cout << "Part 2: " << find_min(possible_folders);
  
    return 0;
}