#include <iostream>
#include <vector>
#include <set>

#include "../libcpp/io.cpp"

using vector_str = std::vector<std::string>;

int detect_marker(const std::string signal, int length);

int main()
{
    vector_str file = import_file("input/d06.txt");
    std::string signal = file[0];

    std::cout << "Part 1: " << detect_marker(signal, 4) << std::endl;
    std::cout << "Part 2: " << detect_marker(signal, 14);
    
    return 0;
}


int detect_marker(const std::string signal, int length)
{
    int result;
    for (int i = 0; i < signal.size(); i++)
    {
        std::set<char> checker;
        for (int j = 0; j < length; j++) checker.insert(signal[i + j]);
        
        // check length
        if (checker.size() == length) {
            result = i + length;
            break;
        }
    }
    return result;
}