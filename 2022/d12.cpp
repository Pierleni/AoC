#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <tuple>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using pt2 = std::pair<int, int>;
using grid = std::vector<std::vector<int>>;

//operator[](T) { return std::get<std::is_placeholder<T>::value>(items); }

int at(grid &matrix, pt2 pos) { return matrix[pos.first][pos.second];}
pt2 add(pt2 a, pt2 b) {return {a.first + b.first, a.second + b.second};}


bool validate(grid &matrix, pt2 pos) {
    return pos.first >= 0 && pos.first < matrix.size() &&
        pos.second >= 0 && pos.second < matrix[0].size();
}



int bfs(grid &matrix, pt2 start, pt2 end) 
{
    std::deque<std::pair<pt2, int>> queue;
    queue.push_back({start, 0});
    std::set<pt2> seen;
    seen.insert(start);
    while (!queue.empty()) 
    {
        auto [coord, dist] = queue.front();
        int value = at(matrix, coord);
        queue.pop_front();
        static constexpr pt2 kDirs[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i = 0; i < 4; i++) {
            pt2 nps = add(coord, kDirs[i]);
            if (!validate(matrix, nps)) continue;
            if (matrix[nps.first][nps.second] - value > 1) continue;
            if (seen.count(nps)) continue;
            if (nps == end) return dist + 1;
            seen.insert(nps);
            queue.push_back({nps, dist + 1});
        }
    }
    return INT16_MAX;
}


std::tuple<grid, pt2, pt2> parse(std::string path)
{
    grid matrix;
    pt2 start, end;
    std::vector<std::string> file = import_file(path);
    for (int y=0; y<file.size(); y++) {
        matrix.emplace_back();
        for (int x=0; x<file[0].size(); x++) {
            char c = file[y][x];
            if (c == 'S') {
                start = {y, x};
                matrix.back().push_back(0);
            } else if (c == 'E') {
                end = {y, x};
                matrix.back().push_back('z' - 'a');
            } else {
                matrix.back().push_back(c - 'a');
            }
        }
    }
    return {matrix, start, end};
}


int fewest_steps(grid &matrix, pt2 start, pt2 end) 
{
    std::vector<pt2> possible_start;
    vector_int all_result;
    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[0].size(); x++) {
            if (matrix[y][x] == 0) {
                all_result.push_back(bfs(matrix, std::make_pair(y, x), end));
            }
        }
    }
    std::sort(all_result.begin(), all_result.end());
    return all_result[0];
    
}


int main()
{
    auto [matrix, start, end] = parse("input/d12.txt");

    std::cout << "Part 1: " << bfs(matrix, start, end) << std::endl;
    std::cout << "Part 2: " << fewest_steps(matrix, start, end);
    
    return 0;
}
