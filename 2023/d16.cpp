
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

using pos = pair<int,int>;
using Matrix = vector<vector<char>>;
using Splitter = map<char,vector<char>>;
using Lens = map<char,char>;

map<char,pos> card = {{'n',{-1,0}},{'s',{1,0}},{'w',{0,-1}},{'e',{0,1}}};
Lens slash = {{'n','e'},{'s','w'},{'e','n'},{'w','s'}}; // '/'
Lens backSlash = {{'n','w'},{'s','e'},{'w','n'},{'e','s'}}; // '\'
Splitter vertical = {{'n',{'n'}},{'s',{'s'}},{'w',{'n','s'}},{'e',{'n','s'}}};  // '|';
Splitter horizzontal = {{'e',{'e'}},{'w',{'w'}},{'n',{'w','e'}},{'s',{'w','e'}}};  // '-';

pos operator+(pos &a, pos &b) {return {a.first + b.first, a.second + b.second};}
bool inBound(pos &p, Matrix &m) {
    return (p.first >= 0 && p.first < m.size()) && (p.second >= 0 && p.second < m[0].size());
}

int64_t countTiles(Matrix &m) {
    int64_t count = 0;
    for (int y = 0; y < m.size(); y++) {
        for (int x = 0; x < m[y].size(); x++){
            if (m[y][x] == '#') count++;
        }
    }
    return count;
}

int64_t bfs(Matrix &matrix, pos start, char d)
{
    Matrix new_matrix = matrix;
    
    deque<pair<pos,char>> que;
    que.push_back({start, d});
    
    set<pair<pos,char>> seen;
    seen.insert({start, d});
    
    set<pair<pos,char>> seen2;
    seen2.insert({start, d});

    while (!que.empty())
    {
        
        pos cur = que.front().first;
        char face = que.front().second;
        que.pop_front();
        
        pos nextPos;
        vector<pair<pos,char>> possibleDirections;
        char space = matrix[cur.first][cur.second];
        
        new_matrix[cur.first][cur.second] = '#';
        
        if (space == '.' || space == '#') {
            nextPos = cur + card[face];
            possibleDirections.push_back({nextPos,face});
        }
        if (space == '/') {
            face = slash[face];
            nextPos = cur + card[face];
            possibleDirections.push_back({nextPos,face});
        }
        if (space == '\\') {
            face = backSlash[face];
            nextPos = cur + card[face];
            possibleDirections.push_back({nextPos,face});
        }
        if (space == '-') {
            for (char c : horizzontal[face]) {
                nextPos = cur + card[c];
                possibleDirections.push_back({nextPos,c});
            }
        }
        if (space == '|') {
            for (char c : vertical[face]) {
                nextPos = cur + card[c];
                possibleDirections.push_back({nextPos,c});
            }
        }

        for (pair<pos,char>  path : possibleDirections) {
            if (!inBound(path.first, matrix)) continue;
            
            if (seen.count({path.first, path.second})) continue;
            seen.insert({path.first, path.second});

            if (seen2.count({path.first, path.second})) continue;
            seen2.insert({path.first, path.second});

            que.push_back(path);
        }
    }
    return countTiles(new_matrix);

}
            
int main()
{
    pos start = {0,0};
    Matrix matrix;

    std::vector<std::string> file = import_file( "input/d16.txt" );
    for (string line : file) {
        vector<char> tmp;
        matrix.push_back(tmp);
        for (char c : line) {
            matrix.back().push_back(c);
        }
    }
    
    cout << bfs(matrix, start,'e') << endl;

    int64_t part2 = 0;

    for (int y=0; y<matrix.size(); y++) {
        part2 = max(part2, bfs(matrix, {y,0},'e'));
        part2 = max(part2, bfs(matrix, {y,matrix[0].size()-1},'w'));
    }

    for (int x=0; x<matrix[0].size(); x++) {
        part2 = max(part2, bfs(matrix, {0,x},'s'));
        part2 = max(part2, bfs(matrix, {matrix.size()-1,x},'n'));
    }
    cout << part2;         

    return 0;
}