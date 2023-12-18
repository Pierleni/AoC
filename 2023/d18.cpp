
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

using namespace std;

using pt = pair<int64_t,int64_t>;

pt operator +(pt &a, pt &b) {
    return {a.first + b.first, a.second + b.second};
}

void bfs(set<pt> &per) {
    deque<pt> que;
    que.push_back({1,1});
    set<pt> seen;
    seen.insert({1,1});

    while (!que.empty()) {
        pt cur = que.front();
        que.pop_front();

        pt d[] = {{0,1},{0,-1},{1,0},{-1,0}};
        for (int64_t i=0; i<4; i++) {
            pt npos = cur + d[i];

            if (per.count(npos)) continue;
            if (seen.count(npos)) continue;

            per.insert(npos);
            seen.insert(npos);
            que.push_back(npos);
        }
    }  
    cout << per.size()+1 << endl;   
}
            
int main()
{
    int64_t maxY, maxX = 0;
    int64_t minY, minX = INT64_MAX;
    map<char,pt> dirs = {{'R',{0,1}},{'D',{1,0}},{'L',{0,-1}},{'U',{-1,0}}};
    map<char,pt> dirs2 = {{'0',{0,1}},{'1',{1,0}},{'2',{0,-1}},{'3',{-1,0}}};
    pt cur_pos = {0,0};
    set<pt> perimeter = {cur_pos};
    std::vector<std::string> file = import_file( "input/d18.txt" );
    for (string l : file) {
        vector<string> words = line_to_words(l);
        char dir = words[0][0];
        int64_t step = convert_to<int64_t>(words[1]);
        string color = words[2];

        for (int64_t i=0; i<step; i++) {
            cur_pos = cur_pos + dirs[dir];
            perimeter.insert(cur_pos);
        }
    }
    bfs(perimeter);

    //////////////////// P A R T 2
 
    int64_t y = 0; 
    int64_t x = 0; 
    int64_t perim = 0; 
    vector<pt> borders;

    for (string l : file) {
        vector<string> words = line_to_words(l);
        string color = words[2];
        
        // get dir
        char direct = color[color.size()-2];
        
        // get step converting frm hex
        string subCol = color.substr(2,5);
        char *array = new char[5];
        strcpy(array, subCol.c_str()); 
        int steps = (int)stol(array, NULL, 16);

        borders.push_back({x, y});
        perim += steps;
        x += dirs2[direct].first * steps;
        y += dirs2[direct].second * steps;
    }

    // Shoelace formula
    int64_t area = 0;
    for (int64_t i=0; i<borders.size()-1; i++) {
        pt a = borders[i];
        pt b = borders[i+1];
        area += a.first * b.second - b.first * a.second;
    }
    area = abs(area) / 2;

    int64_t interior_area = area - perim / 2 + 1;
    cout << interior_area + perim<< endl;
 
    return 0;
}