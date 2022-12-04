#include <iostream>
#include <fstream>
#include <vector>



// IMPORT
std::vector<std::string> import_file(std::string path)
{
    std::vector<std::string> matrix;
    std::ifstream input(path);
    std::string line;
    while (std::getline (input, line)) {
        matrix.push_back(line);
    }
    return matrix;
}


// PRINT VECTOR
template <class T>
void show_content(std::vector<T> file)
{
    for (auto f : file) {
        std::cout << f << std::endl;
    }
}


// PRINT STRING
void prints(std::string word, char c=' ') 
{
    std::cout << word << c;
}
// PRINT INTEGER
void printi(int n, char c=' ')
{
    std::cout << n << c;
}