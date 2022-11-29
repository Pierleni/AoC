#include <iostream>
#include <string>
#include <vector>


// SLICE VECTOR
template <class T>
std::vector<T> slice_vector(int start, int end, std::vector<T> &vec)
{
    std::vector<T> result(end - start);

    auto x = vec.begin() + start;
    auto y = vec.begin() + end;
    std::copy(x, y, result.begin());

    return result;
}



int find_min(std::vector<int> matrix)
{
    int min = matrix[0];
    for (size_t i = 0; i < matrix.size(); i++){
        if (matrix[i] < min) min = matrix[i];
    }
    return min;
    
}



int find_max(std::vector<int> matrix)
{
    int max = matrix[0];
    for (size_t i = 0; i < matrix.size(); i++){
        if (matrix[i] > max) max = matrix[i];
    }
    return max;
    
}