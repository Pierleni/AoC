
#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using namespace std;

vector<vector<char>> matrix;
vector<vector<char>> matrix_copy;
vector<pair<int64_t,int64_t>> galax;

int manhattan(pair<int,int> a, pair<int,int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

bool isEmptyV(int x) {
    for (int y=0; y<matrix.size(); y++) {
            if (matrix[y][x] == '#') return false;
        } 
    return true;

}

bool isEmpty(vector<char> &vec) {
    for (int x = 0; x < vec.size(); x++) {
        if (vec[x] == '#') return false;
    }
    return true; 
}

            
int main()
{
    std::vector<std::string> file = import_file( "input/d11.txt" );
    for (int y=0; y<file.size(); y++) {
        vector<char> vec;
        matrix.push_back(vec);
        for (int x=0; x<file[y].size(); x++) {
            matrix.back().push_back(file[y][x]);
        }
    }
        int factor = 1;

    map<int64_t,int64_t> ofsetX;
    map<int64_t,int64_t> ofsetY;

    for (int y = 0; y < matrix.size(); y++)
    {
        for (int x = 0; x < matrix[y].size(); x++)
        {
            if (matrix[y][x] == '#') galax.push_back({y, x});
        }
        
    }
    
    int64_t count = 0;
    for (int x = 0; x < matrix[0].size(); x++)
    {
        if (isEmptyV(x)) {
            count++;
        }
        ofsetX[x] = factor * count;
    }

    count = 0;
    for (int y = 0; y < matrix[0].size(); y++)
    {
        if (isEmpty(matrix[y])) {
            count++;
        }
        ofsetY[y] = factor * count;
    }

    int64_t ans;
    for (auto p1 : galax) {
        for (auto p2 : galax) {
            int64_t y1 = p1.first + ofsetY[p1.first]; 
            int64_t x1 = p1.second + ofsetX[p1.second];
            int64_t y2 = p2.first + ofsetY[p2.first]; 
            int64_t x2 = p2.second + ofsetX[p2.second];
            int64_t man = manhattan(make_pair(y1,x1), make_pair(y2,x2));
            ans += man;
        }
    }
    cout << (ans/2);

    // // insert rows
    // matrix_copy = matrix;
    // int count = 0; // keep trace of insertions
    // for (int y = 0; y < matrix_copy.size(); y++) {
    //     if (isEmpty(matrix_copy[y])) { 
    //         vector<char> tmp;
    //         for (int x = 0; x < matrix[y].size(); x++) {
    //             tmp.push_back('.');
    //         }
    //         matrix.insert(matrix.begin() + y + count, tmp);
    //         count++;
    //     }
    // }
    // // insert column
    // count = 0;
    // for (int x=0; x<matrix_copy[0].size(); x++) {
    //     if (isEmptyV(x)) {
    //         for (int y = 0; y < matrix.size(); y++) {
    //             matrix[y].insert(matrix[y].begin() + x + count, '.');
    //         }
    //         count++;
    //     }
    // }

    // for (int y = 0; y < matrix.size(); y++) {
    //     for (int x = 0; x < matrix[y].size(); x++) {
    //         if (matrix[y][x] == '#') 
    //             galax.push_back(make_pair(y, x));
    //     }
    // }

    // int ans = 0;
    // show_matrix(matrix);
    // for (auto p1 : galax) {
    //     for (auto p2 : galax) {
    //         if (p1 != p2) {
    //             int man = manhattan(p1, p2);
    //             ans += man;
    //         }
    //     }
    // }
    // cout << ans/2;

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////


    
    return 0;
}