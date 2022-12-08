#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

bool is_visible(int y, int x, std::vector<std::vector<int>> &matrix, int HEIGHT, int WEIGTH);
int best_view(int y, int x, std::vector<std::vector<int>> &matrix, int HEIGHT, int WEIGTH);


int main()
{
    vector_str file = import_file("input/d08.txt");
    std::vector<std::vector<int>> matrix;
    std::vector<int> visible_tree;
    std::vector<int> scenic_view;
    
    int HEIGHT, WEIGTH;
    
    for (std::string line : file) 
    {
        std::vector<int> row;
        
        for (char c : line) {
            row.push_back((int)c - '0');
        }
        matrix.push_back(row);
    }
    
    HEIGHT = matrix.size();
    WEIGTH = matrix[0].size();
    int visible_edge = (HEIGHT * 2) + ((WEIGTH - 2) * 2);

    for (size_t y = 1; y < HEIGHT - 1; y++) {
        for (size_t x = 1; x < WEIGTH - 1; x++)
        {
            scenic_view.push_back(best_view(y, x, matrix, HEIGHT, WEIGTH)); // Part 2

            if (is_visible(y, x, matrix, HEIGHT, WEIGTH)) {                 // Part 1
                visible_tree.push_back(matrix[y][x]);
            }
        }
    }

    std::cout << "Part 1: " << visible_edge + visible_tree.size() << std::endl;
    std::cout << "Part 2: " << find_max(scenic_view);

    return 0;
}


bool is_visible(int y, int x, std::vector<std::vector<int>> &matrix, int HEIGHT, int WEIGTH) 
{   
    /* all of the other trees between it 
    and an edge of the grid 
    are shorter than it */
    bool up, down, left, right;
    up = 1; down = 1; left = 1; right = 1;
    for (size_t ny = 0; ny < y; ny++){
        if (matrix[ny][x] >= matrix[y][x]) up = false;   // not visible
    }
    for (size_t ny = y + 1; ny < HEIGHT; ny++){
        if (matrix[ny][x] >= matrix[y][x]) down = false;
    }
    for (size_t nx = 0; nx < x; nx++) {
        if (matrix[y][nx] >= matrix[y][x]) left = false;
    }
    for (size_t nx = x + 1; nx < WEIGTH; nx++) {
        if (matrix[y][nx] >= matrix[y][x]) right = false;
    }

    if (!up && !down && !left && !right) return false;   // covered in every sides
    else return true;                                    // visible

} 


int best_view(int y, int x, std::vector<std::vector<int>> &matrix, int HEIGHT, int WEIGTH) 
{
    int up, down, left, right;
    up = 0; down = 0; left = 0; right = 0;

    for (int ny = y-1; ny > -1; --ny) 
    {   up++;
        if (matrix[ny][x] >= matrix[y][x]) 
            break;
    }
    for (int ny = y + 1; ny < HEIGHT; ny++) 
    {   down++;
        if (matrix[ny][x] >= matrix[y][x]) 
            break;
    }
    for (int nx = x-1; nx > -1; nx--) 
    {   left++;
        if (matrix[y][nx] >= matrix[y][x]) 
            break;
    }
    for (int nx = x + 1; nx < WEIGTH; nx++) 
    {   right++;
        if (matrix[y][nx] >= matrix[y][x]) 
            break;
    }
    return up * down * left * right;
}