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

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

using namespace std;

// const
std::vector<vector_int> matrix;
using point = std::pair<int,int>;

// functions
void print_point(point p)
{
    if (p.first >= 50 || p.second >= 50) {
        std::cout << "coord " << p.first << ' ' << p.second << '\n';
        std::cout << "content " << matrix[p.first][p.second];
    }
}


point add(point a, point b) {
    return {a.first + b.first, a.second + b.second};
}


bool inBounds(point p) {
    return (0 <= p.first && p.first < matrix.size()) && (0 <= p.second && p.second < matrix[0].size());
}


int bfs(point start, point target)
{
    deque<tuple<set<point>, point,int>> que;
    set<tuple<point,int>> seen;
    que.push_back({{start},{start},0});
    seen.insert({{start}, 0});
    int lowest_result = INT16_MAX;

    while (!que.empty())
    {
        set<point> path = get<0>(que.front());
        point curr = get<1>(que.front());
        int value = get<2>(que.front());
        que.pop_front();


        if (curr == target) {
            lowest_result = lowest_result > value ? value : lowest_result;
            continue;
        }

        static constexpr point dirs[] = {{1,0},{0,1}};
        for (int i = 0; i < 2; i++)
        {
            point npt = add(curr,  dirs[i]);
            if (!inBounds(npt)) continue;
            if (path.count(npt)) continue;
            if (seen.count({{npt}, value})) continue;

            path.insert(npt);
            que.push_back({path,{npt},value + matrix[npt.first][npt.second]});
            seen.insert({{npt}, value + matrix[npt.first][npt.second]});
        }
    }
    return lowest_result;
}


int main()
{  
    vector_str file = import_file("python/input/d15.txt");

    // feed matrix
    for (string line : file) {
        vector_int v;
        for (char c : line) {
            v.push_back(c - '0');
        }
        matrix.push_back(v);
    }

    point start = {0,0};
    point target = {matrix.size()-1, matrix[0].size()-1};

    cout << bfs(start, target); 

    return 0;
}