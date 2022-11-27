#include <iostream>
#include <vector>


template <class T>
std::vector<std::vector<T>> make_matrix2D(int yMax, int xMax, T def)
{
    std::vector<std::vector<T>> matrix;
    for (size_t y = 0; y < yMax; y++) {

        std::vector<T> v;
        for (size_t x = 0; x < xMax; x++){  
            v.push_back(def);
        }
        matrix.push_back(v);
    }
    return matrix;
}



template <class T>
void show_matrix(std::vector<std::vector<T>> &matrix)
{
    for (size_t y = 0; y < matrix.size(); y++)
    {
        for (size_t x = 0; x < matrix[0].size(); x++)
        {
            std::cout << matrix[y][x] << ' ';
        }
        std::cout <<'\n';        
    }  
}