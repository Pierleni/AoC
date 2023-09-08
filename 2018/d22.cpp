#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <deque>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using namespace std;

using ttt = std::tuple<int,int,int>;
using tttt = std::tuple<int,int,int,int>;

int yi = 16807;
int xi = 48271;
int mod = 20183;

enum {rocky, wet, narrow};
enum {torch, gear, neither};

int depth, tY, tX;
std::vector<std::vector<int>> matrix;
std::map<std::pair<int,int>, int64_t> erosion;

//functions
void display_matrix(std::vector<std::vector<int>> &m);
void geologic_index(int y, int x);
int count_risk(std::vector<std::vector<int>> &m);
int bfs(std::pair<int,int> target);
bool inBound(int y, int x);

int main()
{
    std::vector<std::string> lines = import_file("input/d22.txt");
    std::string tmp = "";
    replace_char(lines[1], ',',' ');
    std::string bothLines = lines[0] + lines[1];
    std::stringstream ss(bothLines);
    ss >> tmp >> depth >> tmp >> tX >> tY;


    // create matrix 0 value as default
    for (int y = 0; y < tY * 7; y++) {
        std::vector<int> v;
        matrix.push_back(v);
        for (int x = 0; x < tX * 7; x++) {
            matrix.back().push_back(0);
        }
    }
    
    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[0].size(); x++) {
            geologic_index(y, x);
            matrix[y][x] = erosion[{y, x}] % 3;
        }
    }

    cout << count_risk(matrix) << endl; // 11462

    cout << bfs(std::make_pair(tY,tX));


    return 0;
}



void geologic_index(int y, int x)
{
    int64_t parz;
    if ( y == 0 && x == 0 ) { erosion[{0,0}] = (0 + depth) % mod; }
    else if ( y == tY && x == tX ) { erosion[{tY,tX}] = (0 + depth) % mod; }
    else if ( y == 0 && x != 0 ) { erosion[{y, x}] = (((x * yi) + depth) % mod); }
    else if ( x == 0 && y != 0 ) { erosion[{y, x}] = (((y * xi) + depth) % mod); }
    else if ( x != 0 && y != 0 ) { erosion[{y, x}] = ((erosion[{y-1,x}] * erosion[{y,x-1}]) + depth) % mod; }
}



int count_risk(std::vector<std::vector<int>> &m)
{
    int result = 0;
    for (int y = 0; y <= tY; y++) {
        for (int x = 0; x <= tX; x++) {
            result += m[y][x];
        }
    }
    return result;
}



bool inBounds(int y, int x) {
    return (0 <= y && y < matrix.size()) && (0 <= x && x < matrix[0].size());
}



bool checkTools(int typ, int tool) {
    if(typ == rocky && (tool==torch || tool==gear)) { return true; }
    if(typ == wet && (tool==gear || tool==2)) { return true; }
    if(typ == narrow && (tool==torch || tool==2)) { return true; }
    return false;
}




int bfs(std::pair<int,int> target)
{
    priority_queue<tttt> que;
    std::set<ttt> seen;
    que.push(std::make_tuple(0,0,0,0));    // y, x, d, tool

    while (!que.empty())
    {
        int y, x, d, tool;
        std::tie(d, y, x, tool) = que.top(); 
        que.pop();

        d = -d;

        // found
        if (std::make_pair(y, x) == target && tool == torch)
            return d;

        if (seen.count(make_tuple(y, x, tool))) continue;
        seen.insert(make_tuple(y, x, tool));

        for (int t=0; t < 3; t++) {
            if (checkTools(matrix[y][x], t))
                que.push(std::make_tuple(-(d + 7), y, x, t));
        }

        static constexpr std::pair<int,int> dir[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i = 0; i < 4; i++) {
            int ny = y + dir[i].first;
            int nx = x + dir[i].second;
            
            if (!inBounds(ny, nx)) continue;     
            if (checkTools(matrix[ny][nx], tool)) {
                que.push(std::make_tuple(-(d + 1), ny, nx, tool));
            }
        }            
    }

    return -1;
}



// void display_matrix(std::vector<std::vector<int>> &m)
// {
//     for (int y = 0; y < m.size(); y++) {
//         for (int x = 0; x < m[0].size(); x++) {
//             char c;
//             switch (m[y][x]) {
//                 case 0:
//                 c = '.';
//                 break;

//                 case 1:
//                 c = '=';
//                 break;

//                 case 2:
//                 c = '|';
//                 break;
//             }
//             cout << c;
//         }
//         cout << endl;
//     }
// }


