
#include <iostream>
#include <vector>
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

vector<vector<char>> matrix;
set<pair<int,int>> seen;
vector<int> nums;
vector<int> gears;
int gear;

int sumUp(vector<int> &numbers) {
    int ans = 0;
    for (int n : numbers) ans += n;
    return ans;
}

bool inBound(int &y, int &x) {
    return (0 <= y && y < matrix.size()) && (0 <= x && x < matrix[y].size());
}

void check_digit(int y, int x, vector<vector<char>> &matrix) {
    if (isdigit(matrix[y][x]) && !seen.count({y, x})) {
        
        while ((x > 0) && isdigit(matrix[y][x-1])) {
            x -= 1;
        }

        string n = "";
        while (x < matrix[y].size() && isdigit(matrix[y][x])) {
            seen.insert({y, x});
            n += matrix[y][x];
            x += 1;
        }
        nums.push_back(convert_to<int>(n));
        gear++;
    }
}
            
int main()
{
    vector_str file = import_file( "input/d03.txt" );
    for (int y = 0; y < file.size(); y++) {
        vector<char> v;
        matrix.push_back(v);
        for (int x = 0; x < file[y].size(); x++) {
            matrix.back().push_back(file[y][x]);
        }
    }

    for (int y = 0; y < matrix.size(); y++)
    {
        for (int x = 0; x < matrix[y].size(); x++)
        {
            if (matrix[y][x] != '.' && !isdigit(matrix[y][x])) {

                if (inBound) {
                    pair<int,int> dir[] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,1},{-1,-1},{-1,0}};
                    for (int i=0; i<8; i++) {
                        int yy = y + dir[i].first;
                        int xx = x + dir[i].second;
                        check_digit(yy, xx, matrix);
                    }

                    if (matrix[y][x] == '*' && gear == 2) {
                        gears.push_back(nums[nums.size()-1] * nums[nums.size()-2]);
                    }
                    gear = 0;
                }
            }
        }
    }
    cout << "Part 1: " << sumUp(nums) << endl;
    cout << "Part 2: " << sumUp(gears) << endl;

    return 0;
}