#include <iostream>
#include <vector>
#include <bitset>
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

using namespace std;

const long long letters = 26;        // 26
std::bitset<letters> all_keys;
std::vector<std::vector<char>> matrix;


class Robot
{
    public:
        int Y, X;
        int steps = 0;
        std::bitset<letters> keys;
        Robot(int y, int x, std::bitset<letters> k) : Y(y), X(x) {}
        void print() {
            cout << "pos: " << Y << ' ' << X << '\n';
            cout << "step: " << steps;
            cout << "\nkeys: " << keys << "\n";
            cout << "\n=================\n";
            //getchar();
        }
};



void ignoreDoors(std::vector<Robot> &robots) 
{
    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[y].size(); x++) {
            char c = matrix[y][x];
            if (islower(c)) {
                robots[0].keys[c - 'a'] = (y <= robots[0].Y) && (x <= robots[0].X);
                robots[1].keys[c - 'a'] = (y <= robots[1].Y) && (x >= robots[1].X);
                robots[2].keys[c - 'a'] = (y >= robots[2].Y) && (x <= robots[2].X);
                robots[3].keys[c - 'a'] = (y >= robots[3].Y) && (x >= robots[3].X);
            }
        }
    }
    // Flip the bitset to leave the ones we need
    for (int j=0; j<4; j++) {
        robots[j].keys.flip();
    }
}


int bfs(Robot &r)
{
    std::set<std::tuple<int,int,long long>> seen;
    seen.insert({r.Y,r.X,r.keys.to_ullong()});
    std::deque<Robot> que;
    que.push_back(r);
    while (!que.empty())
    {
        Robot robot = que.front();
        que.pop_front();
        
        if (robot.keys.all())
            return robot.steps;
        
        static constexpr std::pair<int,int> pts[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<4; i++) {
            Robot tmp = robot;
            tmp.Y = tmp.Y + pts[i].first;
            tmp.X = tmp.X + pts[i].second;
            char c = matrix[tmp.Y][tmp.X];
            
            if (c == '#') continue;
            if (seen.count({tmp.Y, tmp.X, tmp.keys.to_ullong()})) continue;

            if (islower(c)) 
                tmp.keys[c - 'a'] = 1;
            
            seen.insert({tmp.Y, tmp.X, tmp.keys.to_ullong()});
            tmp.steps += 1;
            que.push_back(tmp);
        }
    }
    return 0;
}


int main()
{
    int cy, cx;
    std::vector<Robot> robots;
    vector_str file = import_file("input/d18.txt");
    for (int y=0; y<file.size(); y++) {
        std::vector<char> v;
        matrix.push_back(v);
        for (int x=0; x<file[0].size(); x++) {
            char c = file[y][x];
            if (c == '@') {cy = y; cx = x; c = '#';}
            matrix.back().push_back(c);                         // feed matrix
        }
    }

    matrix[cy-1][cx] = '#';
    matrix[cy+1][cx] = '#';
    matrix[cy][cx-1] = '#';
    matrix[cy][cx+1] = '#';
    matrix[cy-1][cx-1] = '@';
    matrix[cy-1][cx+1] = '@';
    matrix[cy+1][cx-1] = '@';
    matrix[cy+1][cx+1] = '@';
    robots.push_back(Robot(cy-1, cx-1, 0));
    robots.push_back(Robot(cy-1, cx+1, 0));
    robots.push_back(Robot(cy+1, cx-1, 0));
    robots.push_back(Robot(cy+1, cx+1, 0));

    ignoreDoors(robots);

    int total_steps = 0;
    for (int k=0; k<4; k++) {
        total_steps += bfs(robots[k]);
    }
    std::cout << "Part 2: " << total_steps;

    return 0;
}