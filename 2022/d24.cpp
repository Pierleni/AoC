#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
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

//#define DEBUG

using namespace std;

using pt = pair<int,int>;

int mod(int size, int n) {return ((n % size) + size) % size;}  // negative index for wrap around
pt add(const pt &a, const pt &b) {return {a.first + b.first, a.second + b.second};}

int H, W;
pt start = {0,0};
pt target = {0,0};
vector<vector<char>> matrix;
map<int, set<pair<int,int>>> NO_SPOT;

void bfs(pt start, vector<vector<char>> &matrix);
bool inBound(pt p) {
    return (0<=p.first && p.first<= H-1) && (0<=p.second && p.second<= W-2) && (matrix[p.first][p.second] != '#');
}

int main()
{
    vector_str file = import_file("input/d24.txt");
    // popolate matrix
    for (string &line : file) {
        vector<char> v;
        matrix.push_back(v);
        for (char &c : line) {
            matrix.back().push_back(c);
        }
    }
    H = matrix.size();
    W = matrix[0].size();

    while (matrix[start.first][start.second] == '#') {
        start.second++;
    }
    target = {H-1,0};
    while (matrix[target.first][target.second] == '#') {
        target.second++;
    }
    cout << "Start: " << start.first << ' ' << start.second << endl;
    show_matrix(matrix);
    cout << H << ' ' << W;

    // find all blind spot a time 't' and populate NO_SPOT
    for (int t = 0; t < ((W-2) * (H-2) * 2); t++)
    {
        set<pair<int,int>> bad;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (matrix[y][x] == '>')
                    bad.insert({y, 1 + (x-1 + t) % (W-2)});

                else if (matrix[y][x] == 'v') 
                    bad.insert({1 + (y-1 + t) % (H-2), x});

                else if (matrix[y][x] == '<')
                    bad.insert({y, 1 + mod(W-2, x-1-t)});

                else if (matrix[y][x] == '^') 
                    bad.insert({1 + mod(H-2, y-1-t), x});
            }
        }
        NO_SPOT[t] = bad;
    }
    bfs(start, matrix);    

    return 0;
}



void bfs(pt start, vector<vector<char>> &matrix)
{
    bool half;
    deque<tuple<pt, int, bool, bool>> que;
    set<tuple<pt,int, bool, bool>> seen;
    que.push_back({start, 0, false, false});
    while (!que.empty())
    {
        pt curr     = get<0>(que.front());
        int t       = get<1>(que.front());
        bool pt1    = get<2>(que.front());
        bool pt2    = get<3>(que.front());
        que.pop_front();
        
        if (seen.count({curr, t, pt1, pt2})) continue;

        if (curr == target && pt1 && pt2) {
            cout << "\nPart 2: " << t;
            break;
        }
        if (curr == target && !half) {
            cout << "\nPart 1: " << t;
            half = true;
            pt2 = true;
        }
        if (curr == start && half) 
            pt1 = true;


        seen.insert({curr, t, pt1, pt2});


        static constexpr pt dir[] = {{-1,0},{1,0},{0,-1},{0,1}};
        for (int i=0; i<4; i++) {
            pt npt = add(curr, dir[i]);
            if (!inBound(npt)) continue;
            if (NO_SPOT[t].count(curr)) {que.push_back({curr, t+1, pt1, pt2}); continue;}
            if (NO_SPOT[t+1].count(npt)) {que.push_back({curr, t+1, pt1, pt2}); continue;}
            que.push_back({npt, t+1, pt1, pt2});
        }
    }
}
