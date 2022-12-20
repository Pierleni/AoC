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
using pt = std::pair<int, int>;


// #define SIZE 5

using namespace std;


pt add(pt a, pt b) {return {a.first + b.first, a.second + b.second};}


void catch_portal_y(int y, int x, int delta, 
                    vector<vector<char>> matrix, 
                        map<string, vector<pair<int, int>>> &portal_list) 
{
    string tmp;
    tmp += matrix[y][x];
    tmp += matrix[y+1][x];
    pt point = {y + (delta), x};
    portal_list[tmp].push_back(point);
}


void catch_portal_x(int y,int x,int delta,
                    vector<vector<char>> matrix,
                        map<string,vector<pair<int,int>>> &portal_list)
{
    string tmp;
    tmp += matrix[y][x];
    tmp += matrix[y][x+1];
    pt point = {y, x + (delta)};
    portal_list[tmp].push_back(point);
}


int bfs(pt start, pt end, vector<vector_char> matrix, map<pt, pt> AtoB)
{
    set<pt> seen;
    seen.insert(start);
    deque<pair<pt,int>> queue;
    queue.push_back({start, 0});
    while (!queue.empty()) 
    {
        auto [point, dist] = queue.front();
        queue.pop_front();
        if (point == end) 
            return dist;
        static constexpr pt neigh[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i = 0; i < 4; i++) {
            pt np = add(point, neigh[i]);
            if ((int)matrix[np.first][np.second] >= 65) continue;   // its a letter
            if (matrix[np.first][np.second] == '#') continue;       // its a wall
            if (seen.count(np)) continue;                           // seen
            if (AtoB.count(np)) {
                queue.push_back({AtoB[np], dist + 2});
                continue;
            }
            seen.insert(np);
            queue.push_back({np, dist + 1});
        }
    }
    return -1;
}


int bfs2(pt start, pt end, int level, vector<vector_char> &matrix,map<pt, pt> External, map<pt, pt> Internal  /*TODO*/)
{
    set<pair<pt, int>> seen;
    seen.insert({start, level});
    deque<tuple<pt,int, int>> queue;
    queue.push_back({start, 0, level});
    while (!queue.empty())
    {
        auto [point, dist, lvl] = queue.front();
        queue.pop_front();
        if ((point == end) && (lvl == 0)) return dist;
        static constexpr pt neigh[] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int i = 0; i < 4; i++) {
            pt np = add(point, neigh[i]);
            if ((int)matrix[np.first][np.second] >= 65) continue;   // its a letter
            if (matrix[np.first][np.second] == '#') continue;       // its a wall
            if (seen.count({np, lvl})) continue;
            if (Internal.count(np)) {
                queue.push_back({Internal[np], dist + 2, lvl + 1});
                continue;
            }
            if (External.count(np) && (lvl > 0)) {
                queue.push_back({External[np], dist + 2, lvl - 1});
                continue;
            }
            seen.insert({np, lvl});
            queue.push_back({np,dist+1,lvl});
        }
    }
    return -1;
}


int main()
{
    int SIZE = 0;
    pt start, end;
    map<pt, pt> AtoB;
    map<pt, pt> External;
    map<pt, pt> Internal;
    vector<vector_char> matrix;
    map<string, vector<pair<int, int>>> portal_list;
    map<string, vector<pair<int, int>>> ext_portal;
    map<string, vector<pair<int, int>>> int_portal;

    // Create matix
    vector_str file = import_file("input/d20.txt");
    for (int y = 0; y < file.size(); y++) {
        vector_char v1;
        for (int x = 0; x < file[y].size(); x++) {
            v1.push_back(file[y][x]);
        }
        matrix.push_back(v1);        
    }
    // Find Size
    for (int y = matrix.size()/2; y < (matrix.size()/2)+1; y++) {
        for (int x = 2; x < matrix[y].size(); x++) {
            if ((matrix[y][x] != '#') && (matrix[y][x] != '.')) break;
            else SIZE++;
        }        
    }
    
    // Parse Portals UP
    for (int y = 0; y < 1; y++) {
        for (int x = 0; x < matrix[y].size(); x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_y(y, x, 2, matrix, portal_list);
                catch_portal_y(y, x, 2, matrix, ext_portal);
            }
        }
    }
    // Parse Portals Bottom
    for (int y = matrix.size() - 2; y < matrix.size() - 1; y++) {
        for (int x = 0; x < matrix[y].size(); x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_y(y, x, -1, matrix, portal_list);
                catch_portal_y(y, x, -1, matrix, ext_portal);
            }
        }
    }
    // Left
    for (int y = 2; y < matrix.size(); y++) {
        for (int x = 0; x < 1; x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_x(y,x,2,matrix,portal_list);
                catch_portal_x(y,x,2,matrix,ext_portal);

            }
        }
    }
    // Right
    for (int y = 2; y < matrix.size(); y++) {
        for (int x = matrix[y].size()-2; x < matrix[y].size()-1; x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_x(y,x,-1,matrix,portal_list);
                catch_portal_x(y,x,-1,matrix,ext_portal);

            }
        }
    }
    // int Upper y
    for (int y = SIZE + 2; y < SIZE + 3; y++) {
        for (int x = SIZE + 4; x < matrix[y].size() - (SIZE + 4); x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_y(y, x, -1, matrix, portal_list);
                catch_portal_y(y, x, -1, matrix, int_portal);
            }
        }
    }
    // int Lower y
    for (int y = matrix.size() - (SIZE + 4); y < matrix.size() - (SIZE + 4) + 1; y++) {
        for (int x = SIZE + 4; x < matrix[y].size() - (SIZE + 4); x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_y(y, x, 2, matrix, portal_list);
                catch_portal_y(y, x, 2, matrix, int_portal);
            }
        }
    }
    // Int Left
    for (int y = SIZE + 2; y < matrix.size() - (SIZE + 2); y++) {
        for (int x = SIZE + 2; x < SIZE + 3; x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_x(y,x,-1,matrix,portal_list);
                catch_portal_x(y,x,-1,matrix,int_portal);
            }
        }
    }
     // Int Right
    for (int y = SIZE + 2; y < matrix.size()- (SIZE + 2); y++) {
        for (int x = matrix[y].size() - (SIZE + 4); x < matrix[y].size() - (SIZE + 4) + 1; x++) {
            if (matrix[y][x] != ' ') {
                catch_portal_x(y,x,2,matrix,portal_list);
                catch_portal_x(y,x,2,matrix,int_portal);
            }
        }
    }
    start = portal_list["AA"][0];
    end = portal_list["ZZ"][0];
    // Connect Portals
    for (auto portal : portal_list) {
        if ((portal.first != "AA") && (portal.first != "ZZ")) {
            AtoB[portal.second[0]] = portal.second[1];
            AtoB[portal.second[1]] = portal.second[0];
            
            External[ext_portal[portal.first][0]] = int_portal[portal.first][0];
            Internal[int_portal[portal.first][0]] = ext_portal[portal.first][0];
        }
    }

    for (auto portal : External) {
        pt a = portal.first;
        pt b = portal.second;
        for (auto p : ext_portal) {
            if (p.second[0] == a) cout << p.first << '\n';
        }
        cout << "External: "<<a.first << ','<<a.second << ' '<<b.first<<','<<b.second<<endl;
    }
        for (auto portal : Internal) {
        pt a = portal.first;
        pt b = portal.second;
        for (auto p : int_portal) {
            if (p.second[0] == a) cout << p.first << '\n';
        }
        cout << "Internal: "<<a.first << ','<<a.second << ' '<<b.first<<','<<b.second<<endl;
    }
   
    int result = bfs(start, end, matrix, AtoB);
    cout << result << endl;

    auto results2 = bfs2(start, end, 0, matrix, External, Internal);
    cout << results2 << endl;
    


    return 0;
}
