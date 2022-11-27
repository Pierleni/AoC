#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>



// SPLIT BY CHAR
std::vector<std::string> parse_line_byChar(std::string line, char c)
{
    std::string temp;
    std::stringstream ss(line);
    std::vector<std::string> result;

    while (std::getline(ss, temp, c)) {
        result.push_back(temp);
    }
    return result;
}



// SPLIT BY STRING
std::string parse_line_byString(std::string line, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
    }
    return line;
}



// SPLIT ' '
std::vector<std::string> line_to_words(std::string line)
{
    std::vector<std::string> result;
    std::string tmp;

    std::stringstream ss(line);
    while (!ss.eof()) {
        ss >> tmp;
        result.push_back(tmp);
    }

    return result;
}



// REPLACE CHAR 
void replace_char(std::string &line, char old_char, char new_char)
{
    std::replace(line.begin(), line.end(), old_char, new_char);    
}