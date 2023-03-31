#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <deque>
#include <regex>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

//#define DRAW

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

using node = std::pair<int,int>;

std::set<node> all_ndoes;
std::map<node, int> sizes{};
std::map<node, int> useds{};
std::map<node, int> avails{};

int Max_Y = 0;
int Max_X = 0;
node start;
node target;

std::set<std::pair<node,node>> pairs;
std::set<node> full_nodes;

using namespace std;

int manhattan(node a, node b) {return std::abs((a.first - b.first) + (a.second - b.second));}

node operator+(const node &a, const node &b) {
    return {a.first + b.first, a.second + b.second};
}

bool inBounds(node p) {
    return ((0 <= p.first && p.first < Max_X+1) && (0 <= p.second && p.second < Max_Y+1));
}

int bfs(node start, node target) {
    std::set<node> seen;
    std::deque<std::pair<node, int>> q;
    seen.insert(start);
    q.push_back({start, 0});
    while (!q.empty()) 
    {
        std::pair<node, int> el = q.front();
        node pos = el.first;
        int dist = el.second;
        q.pop_front();
        if (pos == target) return dist;
        static constexpr node dir[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<4; i++) {
            node npos = pos + dir[i];
            if (!inBounds(npos) || full_nodes.count(npos)) continue;
            if (seen.count(npos)) continue;
            seen.insert(npos);
            q.push_back({npos, dist + 1});
        }
    }
    return 9999;
}

int main()
{
    vector_str file = import_file("input/d22.txt");
    std::regex pattern(R"([\d]+)");
    for (int i=0; i<file.size(); i++) {
        std::string line = file[i];
        if (line[0] != '/') continue; // ignore first lines
        std::vector<int> data;
        // regex set up
        std::sregex_iterator next(line.begin(), line.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            // parse
            int tmp;
            std::stringstream ss;
            std::smatch match = *next;
            ss << match.str(); ss >> tmp;
            data.push_back(tmp);
            next++;
        }
        int x = data[0], y = data[1], size = data[2], used = data[3], avail = data[4], perc = data[5];
        if (Max_X < x) Max_X = x;
        if (Max_Y < y) Max_Y = y;
        all_ndoes.insert({y,x});
        sizes[{y, x}] = size;
        useds[{y, x}] = used;
        avails[{y, x}] = avail;
    }

    // Part 1
    for (const std::pair<int,int> &a : all_ndoes) {
        for (const std::pair<int,int> &b : all_ndoes) {
            if (sizes[a] == 0) continue;
            if (a == b) continue;
            if ((useds[a] + useds[b]) <= avails[b]) pairs.insert({a,b});

            // for part 2
            if (sizes[a] >= 500) full_nodes.insert(a);
            if (useds[a] == 0) start = a;
            if ((a.first == 0) && (a.second == Max_X)) target = a;

        }
    }
    cout << "Part 1: " << pairs.size() << '\n';
    
    // Part 2
    Max_X++;Max_Y++;
    int corner_distance = manhattan({0,0}, {target});

    int dist_to_target = bfs(start, target);

    int ans2 = dist_to_target + ((corner_distance-1) * 5);
    cout << "Part 2: " << ans2;


    // draw
    #ifdef DRAW
    for (int y=0; y<Max_Y; y++) {
        for (int x=0; x<Max_X; x++) {
            if (full_nodes.count({y, x})) cout << '#';
            else if (std::make_pair(y, x) == start) cout << '@';
            else if (std::make_pair(y, x) == target) cout << 'g';
            else cout << '.';
        }
        cout << '\n';
    }
    #endif

    return 0;
}
