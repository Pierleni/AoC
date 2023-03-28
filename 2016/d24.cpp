#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

//#define DEBUG 1

using point = std::pair<int,int>;

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

std::map<int, point> coord;

vector_str file = import_file("input/d24.txt");


point operator+(const point &a, const point &b) {
    return {a.first + b.first, a.second + b.second};
}

char at(point &p){return file[p.first][p.second]; }


int bfs(point from, int target) {
    // Setting Up
    std::deque<std::pair<int, point>> q;        // {dist, current_point}
    q.push_back({0, from});
    std::set<point> seen;
    seen.insert(from);

    // Run
    while (!q.empty()) 
    {
        std::pair<int,point> tmp = q.front();
        int dist = tmp.first;
        point cur = tmp.second;
        q.pop_front();
        static constexpr point moves[] {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<4; i++) 
        {
            point n_pos = cur + moves[i];
            if (at(n_pos) - '0' == target)
                return dist + 1; 
            if (seen.count(n_pos)) continue;
            if (at(n_pos) == '#') continue;
            q.push_back({dist + 1, n_pos});
            seen.insert(n_pos);
        }
    }
    return -1;
}


void solve(std::vector<int> &numbers, int part=1) {
    std::sort(numbers.begin(), numbers.end());      // INDISPENSABILE PRIMA DELLA PERMUTATION
    std::vector<std::vector<int>> permutations;

    do {
        std::vector<int> temp = numbers;
        temp.insert(temp.begin(), 0);
        if (part == 2) temp.push_back(0);
        permutations.push_back(temp);
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    int shortest_path = INT_MAX;
    for (int i=0; i<permutations.size(); i++) {
        int dist = 0;
        vector_int perm = permutations[i];
        for (int a=0, b=1; b<perm.size(); a++, b++) {
            dist += bfs(coord[perm[a]], perm[b]);
            
        }
        if (shortest_path > dist) {
            shortest_path = dist; 
            std::cout << "SHORTEST: " << shortest_path << '\n';} 
        }
    std::cout << "Part " << part << ": " << shortest_path << '\n';
}


int main()
{
    std::vector<int> numbers;

    for (int y=0; y<file.size(); y++) {
        for (int x=0; x<file[y].size(); x++) {
            if (file[y][x] != '#' 
                && file[y][x] != '.' 
                    && file[y][x] != '0') {
                        coord[file[y][x] - '0'] =  {y, x};                   // all numbers (except 0)
                        numbers.push_back(file[y][x] - '0');
                    }
            if (file[y][x] == '0') {coord[file[y][x] - '0'] =  {y, x};}      // starting point
        }
    }

    solve(numbers);
    solve(numbers, 2);    

    return 0;
}
