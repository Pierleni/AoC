#include <iostream>
#include <vector>
#include <cmath>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;


struct Point 
{
    int Y;
    int X;
};

bool baconExist(std::pair<int,int> p, std::vector<Point> bacons) {
    for(std::vector<Point>::iterator it = bacons.begin(); it!=bacons.end(); it++ ) { 
        if ((it->Y == p.first) && (it->X == p.second)) return true;
    }
    return false;
}

std::tuple<Point, Point> parse_line(std::string line) {
    vector_str words = line_to_words(line);
    int a, b, c, d;
    std::string sx = words[2]; std::string sy = words[3];
    std::string bx = words[8]; std::string by = words[9];
    sx = sx.substr(2, sx.find(',')-2);
    sy = sy.substr(2, sy.find(':')-2);
    bx = bx.substr(2, bx.find(',')-2);
    by = by.substr(2);
    return {{convert_to<int>(sy), convert_to<int>(sx)}, 
                {convert_to<int>(by), convert_to<int>(bx)}};
}


int main()
{
    int line_to_check = 2000000;
    vector_str file = import_file("input/d15.txt");
    std::vector<Point> bacons;
    std::vector<Point> requested_line;
    std::set<std::pair<int, int>> result;
    
    for (std::string line : file) {
        auto [sensor, bacon] = parse_line(line);
        bacons.push_back(bacon);
        int raggio = std::abs(sensor.Y - bacon.Y) + std::abs(sensor.X - bacon.X);
        int dist = std::abs(sensor.Y - line_to_check);
        if (std::abs(sensor.Y - line_to_check) < raggio) {
            std::pair XX = {sensor.X - (raggio - dist), sensor.X + (raggio - dist)};
            for ( int x = XX.first; x<XX.second+1;x++) {
                if (!baconExist({line_to_check, x}, bacons))
                    result.insert({line_to_check, x});
            }
        }
    }
    std::cout << result.size();
    return 0;

    // TODO Part 2
}
