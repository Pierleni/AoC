#include <iostream>
#include <vector>
#include <deque>
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

using block = std::vector<std::vector<int>>;

int W = 7;

struct bPos {int Y,X;};

// void display(std::vector<std::vector<int>> &matrix, bPos &pos, block &curr_block) {
//     // draw block
//     for (int y=0, yb=pos.Y; y<curr_block.size(); y++,yb++) {
//         for (int x=0,xb=pos.X; x<curr_block[0].size(); x++,xb++) {
//             if (curr_block[y][x] == 1) matrix[yb][xb] = 1;
//         }
//     }
//     // deaw matrix
//     for (int y = 0; y < matrix.size(); y++) {
//         for (int x = 0; x < W; x++) {
//             char c;
//             if (matrix[y][x] == 0) c = '.';
//             else if (matrix[y][x] == 1) c = '@';
//             else if (matrix[y][x] == 8) c = '-';
//             else if (matrix[y][x] == 9) c = '#';
//             std::cout << c;
//         }
//         std::cout<<'\n'; 
//     }
//     // clear block position
//     for (int y=0, yb=pos.Y; y<curr_block.size(); y++,yb++) {
//         for (int x=0,xb=pos.X; x<curr_block[0].size(); x++,xb++) {
//             if (curr_block[y][x] == 1) matrix[yb][xb] = 0;
//         }
//     }
// }

void resize_matrix(std::vector<std::vector<int>> &matrix, block curr_block, int &upperLevel) {
    while (upperLevel > 2) {
        matrix.erase(matrix.begin());
        upperLevel--;
    }

    int diff = upperLevel - curr_block.size();
    while (diff < 3) {
        std::vector<int> v; v.resize(7);
        matrix.insert(matrix.begin(), v);
        upperLevel++;
        diff++;
    }
}


void moveBlock(bPos &pos, block &curr_block, std::vector<std::vector<int>> &matrix, int dir) {
    bool possible = true;
    for (int y=0, yb=pos.Y; y<curr_block.size(); y++,yb++) {
        for (int x=0,xb=pos.X; x<curr_block[0].size(); x++,xb++) {
            if (curr_block[y][x] == 1) {
                if (0 > xb + dir || xb + dir >= W || matrix[yb][xb+dir] >= 8) {
                    possible = false; break;
                }
            }
        }
    }
    pos.X = possible ? pos.X + dir : pos.X;
}

bool freeFall(std::vector<std::vector<int>> &matrix, block &curr_block, bPos &pos) {
    for (int y=0, yb=pos.Y; y<curr_block.size(); y++,yb++) {
        for (int x=0, xb=pos.X; x<curr_block[0].size(); x++, xb++) {
            if (curr_block[y][x] == 1) {
                if (matrix[yb + 1][xb] >= 8) return false;
            }
        }
    }
    return true;
}

void landBlock(std::vector<std::vector<int>> &matrix, block &curr_block, bPos &pos, int &upperLevel) {
    for (int y=0, yb=pos.Y; y<curr_block.size(); y++,yb++) {
        for (int x=0, xb=pos.X; x<curr_block[0].size(); x++, xb++) {
            if (curr_block[y][x] == 1) matrix[yb][xb] = 9;
        }
    }
    if (pos.Y < upperLevel) upperLevel = pos.Y;
}


int main()
{
    vector_str file = import_file("input/d17.txt");
    std::string mov = file[0];
    int dir_ptr = 0;
    
    // block and pointer
    int blk = 0;                            // iterator
    block block1{{1,1,1,1}};                // -
    block block2{{0,1,0},{1,1,1},{0,1,0}};  // + 
    block block3{{0,0,1},{0,0,1},{1,1,1}};  // L
    block block4{{1},{1},{1},{1}};          // I
    block block5{{1,1},{1,1}};              // []
    std::vector<block> blocks{block1,block2,block3,block4,block5};
    
    // matrix
    int upperLevel = 0;
    std::vector<std::vector<int>> matrix{{8,8,8,8,8,8,8}}; // floor

    // run
    for (int b = 1; b < 2022; b++)    
    {
        bPos pos = {0,2};
        bool landed = false;
        block curr_block = blocks[blk];
        resize_matrix(matrix, curr_block, upperLevel);

        while (!landed)
        {
            // Push
            char arrow = mov[dir_ptr];
            int direction = arrow == '>' ? 1 : -1;
            moveBlock(pos, curr_block, matrix, direction);
            dir_ptr = (dir_ptr + 1) % mov.size();

            // Fall
            if (!freeFall(matrix, curr_block, pos)) {
                landed = true;
                landBlock(matrix, curr_block, pos, upperLevel);
            }
            else pos.Y += 1; 
        }
        blk = (blk + 1) % blocks.size();
    }
    std::cout << "Part 1: " << matrix.size()-1;

    return 0;
}
