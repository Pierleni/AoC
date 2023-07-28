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

using namespace std;

int all_keys = 0;
std::map<char,char> doors = {};
std::vector<std::vector<char>> matrix;

struct Pt 
{
    int Y;
    int X;
};

struct State 
{
    Pt pos;
    int step = 0;
    std::vector<char> keys = {};
    // Debug
    void print() {
        cout << "pos: " << pos.Y << ' ' << pos.X << '\n';
        cout << "step: " << step << "\nkeys ";
        for (char c : keys) {cout << c << ' ';};
        cout << "\n=================\n";
    }
};


Pt operator+(const Pt &a, const Pt &b) {
    return {a.Y + b.Y, a.X + b.X};
}


int bfs(State state, int target) {
    std::deque<State> que;
    que.push_back(state);
    set<tuple<int,int,vector<char>>> seen;
    while (!que.empty()) {
        State tmp = que.front();
        que.pop_front();

        if (tmp.keys.size() == target) 
            return tmp.step;

        static constexpr Pt pts[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i=0; i<4; i++) {
            State s = tmp;              // create safe copy
            Pt npos = s.pos + pts[i];
            char c = matrix[npos.Y][npos.X];
            
            if (c == '#') 
                continue;

            if (isupper(c) && 
                (find(s.keys.begin(), s.keys.end(), tolower(c))) == s.keys.end())
                    continue;

            sort(s.keys.begin(), s.keys.end());
            tuple<int,int,vector<char>> to_check = {npos.Y, npos.X, s.keys};
            if (seen.count(to_check)) 
                continue;

            if (islower(c)) {
                if (find(s.keys.begin(), s.keys.end(), c) == s.keys.end()) {
                    s.keys.push_back(c);
                    s.print();
                }
            }
            seen.insert({npos.Y, npos.X, s.keys});
            s.pos = npos;
            s.step += 1;
            que.push_back(s);            
        }
    }
    return -1;
}

int main()
{
    int total_keys = 0;
    State state = State();
    vector_str file = import_file("input/d18.txt");
    for (int y=0; y<file.size(); y++) {
        std::vector<char> v;
        matrix.push_back(v);
        for (int x=0; x<file[0].size(); x++) {
            char c = file[y][x];
            if (c == '@') {state.pos.Y = y; state.pos.X = x;};  // start
            if (isupper(c)) doors[c] = tolower(c);              // find door
            if (islower(c)) total_keys++;                       // find keys
            matrix.back().push_back(c);                         // feed matrix
        }
    }

    std::cout << "Part 1: " << bfs(state, total_keys);


    return 0;
}