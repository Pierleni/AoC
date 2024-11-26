#include <iostream>
#include <sstream>
#include <vector>


// CONVERT SINGLE STRING
template <class T>
T convert_to(std::string word)
{
    T result;
    std::stringstream ss(word);
    ss >> result;
    return result;
}



// CONVERT SINGLE CHAR
template <class T>
T convert_char_to(char c)
{
    T result;
    std::stringstream ss(c);
    ss >> result;
    return result;
}



// CONVERT VECTOR TYPE
template <class T>
std::vector<T> convert_vector(std::vector<std::string> line) 
{
    std::vector<T> typeArray;
    T found;

    for (auto word : line) {
        std::stringstream ss(word);
        ss >> found;
        typeArray.push_back(found);
    }
    return typeArray;
}