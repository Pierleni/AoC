#include <iostream>
#include <vector>

#include "../../libcpp/io.cpp"
#include "../../libcpp/slice.cpp"
#include "../../libcpp/parse.cpp"
#include "../../libcpp/grids.cpp"
#include "../../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;
using pt = std::pair<int,int>;

using namespace std;

vector<vector<char>> matrix;
vector<vector<char>> matrix2;
pt dir[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};

pt operator+(pt &a, pt &b) {
    return {a.first + b.first, a.second + b.second};
}

bool inBound(int y, int x) {
    return ((0<=y && y<matrix.size()) && (0<=x && x<matrix[0].size()));
}

int count(vector<vector<char>> &matrix) {
    int n = 0;
    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix[0].size(); x++) {
            if (matrix[y][x] == '#') 
                n++;
        }
    }
    return n;
}

// binary string converter
int convert_binary(string s) {
    int base = 1, result = 0;
    for (int i=s.size()-1; i>=0; i--) {
        if (s[i] == '1') result += base;
        base = base * 2;
    }
    return result;
}

// expand matrix
void expand(vector<vector<char>> &matrix, char filler) {
    vector<char> row;
    for (int i = 0; i < matrix[0].size(); i++) {
        row.push_back(filler);
    }
    matrix.insert(matrix.begin(), row);
    matrix.push_back(row);
    for (int y=0; y<matrix.size(); y++) {
        matrix[y].insert(matrix[y].begin(), filler);
        matrix[y].push_back(filler);
    }
}

int main()
{
    vector_str file = import_file("input/d20.txt");
    string algo = file[0];
    vector<char> fillers = {'.','#'};
    int f;
    if ((algo[0] == '#') && (algo[511] == '.')) f=1;
    else f = 0;
    
    // matrix
    file.erase(file.begin());
    file.erase(file.begin());
    for (int y=0; y<file.size(); y++) {
        vector<char> v;
        matrix.push_back(v);
        for (int x=0; x<file[y].size(); x++) {
            matrix.back().push_back(file[y][x]);
        }
    }

    show_matrix(matrix2);
    std::cout << '\n';

    for (int t=0; t<2; t++) 
    {
        expand(matrix, fillers[f]);
        matrix2 = matrix;

        for (int y = 0; y < matrix.size(); y++) 
        {
            for (int x = 0; x < matrix[0].size(); x++) 
            {
                pt p = {y, x};
                string byt = "";

                for (int i=0; i<9; i++) 
                {
                    pt np = p + dir[i];
                    if (inBound(np.first, np.second)) 
                        byt += matrix[np.first][np.second] == '#' ? '1' : '0';
                    else byt += '0';
                }
                int index = convert_binary(byt);
                matrix2[y][x] = algo[index];
            }
        }
        matrix = matrix2;
        f = (f + 1) % 2;

        show_matrix(matrix2);
        std::cout << '\n';
    }

    std::cout << "\nPart 1: " << count(matrix2);
    
    


    return 0;
}
