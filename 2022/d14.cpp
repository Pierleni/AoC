#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using pt = std::pair<int, int>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_str = std::vector<std::string>;
using grid = std::vector<std::vector<char>>;


pt add(pt a, pt b) {
    return {a.first + b.first, a.second + b.second};
}

bool validate(grid &matrix, pt pos) {
    return pos.first >= 0 && pos.first < matrix.size() &&
        pos.second >= 0 && pos.second < matrix[0].size();
}
bool check_occupied(grid &matrix, pt pos) {
    return matrix[pos.first][pos.second] == 'o' || 
        matrix[pos.first][pos.second] == '#';
}

pt bfs(grid &matrix, pt start) {
    pt full;
    std::deque<pt> queue;
    queue.push_back(start);
    while (!queue.empty()) 
    {
        pt cord = queue.front();
        queue.pop_front();
        static constexpr pt neigh[] = {{1,0},{1,-1},{1,1}};
        for (int i=0; i<3; i++) {
            pt npos = add(cord, neigh[i]);
            if (!validate(matrix, npos)) return {1000,1000};
            if (check_occupied(matrix, npos)) continue;
            else {
                queue.push_back(npos); 
                break;
            };
        }
        if (queue.empty()) full = cord; 
    }
    return full;
}


std::tuple<grid, pt, int> parse(std::string path)
{
    pt start = {0,500};
    vector_int height;
    std::vector<pt> walls;
    vector_str file = import_file("input/d14.txt");

    for (int i = 0; i < file.size(); i++){
        replace_char(file[i], '-',' ');
        replace_char(file[i], '>',' ');
        vector_str line = line_to_words(file[i]);
        
        for (int j = 0; j < line.size()-1; j++) {
            vector_str numbers1 = parse_line_byChar(line[j], ',');
            vector_str numbers2 = parse_line_byChar(line[j+1], ',');
            int y1 = convert_to<int>(numbers1[1]);
            int y2 = convert_to<int>(numbers2[1]);
            int x1 = convert_to<int>(numbers1[0]);
            int x2 = convert_to<int>(numbers2[0]);

            height.insert(height.end(), {y1, y2});

            for (int h = y1; h < y2+1; h++){
                for (int r = x1; r < x2+1; r++){
                    walls.push_back({h, r});
                }
            }
            for (int h = y2; h < y1+1; h++){
                for (int r = x2; r < x1+1; r++){
                    walls.push_back({h, r});
                }
            }
        }
    }
    // find max height
    int hMax = find_max(height) + 2;
    // make grid
    grid matrix = make_matrix2D(200, 1000, '.');
    // draw walls
    for (pt w : walls) 
        matrix[w.first][w.second] = '#'; 
    // draw start point
    matrix[start.first][start.second] = '+';
    return {matrix, start, hMax};
}

int main()
{
    // Part 1
    pt newpt;
    int grain;
    auto [matrix, start, hMax] = parse("input/d14.txt"); 
    while (true) {
        newpt = bfs(matrix, start);
        if (newpt.first == 1000) break;
        matrix[newpt.first][newpt.second] = 'o';
        grain++;
    }
    std::cout << "Part 1: " << grain <<'\n';
    
    // Part 2
    grain=0;
    pt last_pt = {0,0};
    auto [matrix2, start2, hMax2] = parse("input/d14.txt");
    // draw floor at lowest height
    for (int y = hMax2; y < hMax2 + 1; y++) {
        for (int x = 0; x < 1000; x++){
            matrix2[y][x] = '#';
        }
    }
    while (true) {
        newpt = bfs(matrix2, start2);
        if (newpt == start2) break;
        matrix2[newpt.first][newpt.second] = 'o';
        grain++;
    }
    grain++;
    std::cout << "Part 2: " << grain;

    return 0;
}
