#include <iostream>
#include <vector>
#include <regex>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

struct pt {
    int Y;
    int X;
};

char curr_dir = 'E';
pt operator+(pt &a, pt &b) {return {a.Y + b.Y, a.X + b.X};}
std::map<char,char> turnRight = {{'E','S'},{'S','W'},{'W','N'},{'N','E'}};
std::map<char,char> turnLeft = {{'S','E'},{'W','S'},{'N','W'},{'E','N'}};
std::map<char, pt> directions = {{'N', {-1,0}},{'E',{0,1}},{'S',{1,0}},{'W',{0,-1}}};
std::map<char, int> facing = {{'E',0},{'S', 1},{'W', 2},{'N', 3}};

using namespace std;


int w, h;
pt curr_pos = {0,0};
vector_str commands;
vector<vector_int> matrix;

void inBounds1(pt &p);

void show_matrix2(vector<vector_int> &m) {
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            cout << m[y][x];
        }
        cout << y <<'\n';
        if ((y != 0) && (y % 49 == 0)) {getchar();}
    }
}

int main()
{
    /////////////////// parsing matrix
    vector_str file = import_file("input/d22.txt");
    int index=0;
    for (int i=0; i<file.size(); i++, index++) {
        if (file[i] == "") break;
        h += 1;
        if (w < file[i].size()) w = file[i].size();
    }
    
    /////////////////// parsing commands
    regex exp("([0-9]+[LR]|\\d+)");
    vector<string> v;
    smatch res;
    vector_str temp_com;
    string::const_iterator searchStart(file[index+1].begin());
    while (regex_search(searchStart, file[index+1].cend(), res, exp)) {
        temp_com.push_back(res[0]);
        searchStart = res.suffix().first;
    }
    for (string &d : temp_com) {
        if (d.size() == 3) {
            commands.push_back(d.substr(0,2));
            commands.push_back(d.substr(2,1));
        } else if ((d.size() == 2) && 
            ((d[1] == 'L') || (d[1] == 'R'))) {
            commands.push_back(d.substr(0,1));
            commands.push_back(d.substr(1,1));
        } else {
            commands.push_back(d.substr(0,2));
        }
    }


    ////////////////// Create matrix
    for (int y=0; y<h; y++) {
        vector_int v;
        for (int x=0; x<w; x++) {
            int n;
            if (x > file[y].size()-1) v.push_back(0);
            else if (file[y][x] == ' ') v.push_back(0);
            else if (file[y][x] == '.') v.push_back(1);
            else if (file[y][x] == '#') v.push_back(2); 
        }
        matrix.push_back(v);
    }

    ////////////////// Find Start Point
    for (int i=0; i<matrix[0].size(); i++) {
        if (matrix[0][i] == 1) {curr_pos = {0,i}; break;}
    }
    matrix[curr_pos.Y][curr_pos.X] = 9;
    //show_matrix(matrix);
    
    // Part one
    for (int i=0; i<=commands.size(); i++) {
        string op = commands[i];
        if (op == "L" || op == "R") {
            switch ((char)op[0]) 
            {
                case 'L':
                curr_dir = turnLeft[curr_dir];
                break;

                case 'R':
                curr_dir = turnRight[curr_dir];
                break;
            }
        } else {
            int step = convert_to<int>(op);
            for (int j=0; j<step; j++) {
                pt newPos = curr_pos + directions[curr_dir];
                // tutta una serie di controlli
                inBounds1(newPos);
                while (matrix[newPos.Y][newPos.X] == 0) 
                {
                    newPos = newPos + directions[curr_dir];
                    inBounds1(newPos);
                }
                if (matrix[newPos.Y][newPos.X] == 2 ) break;
                curr_pos = newPos;
                matrix[curr_pos.Y][curr_pos.X] = 9;
            }
        }
    }
    int psw1 = (1000 * (curr_pos.Y + 1)) + (4 * (curr_pos.X + 1)) + facing[curr_dir];
    std::cout << "Part 1: " << psw1 << endl;
    return 0;
}


void inBounds1(pt &p) {
    if (p.Y < 0) p.Y = matrix.size()-1;
    if (p.Y == matrix.size()) p.Y = 0;
    if (p.X < 0) p.X = matrix[0].size()-1;
    if (p.X == matrix[0].size()) p.X = 0;
}

