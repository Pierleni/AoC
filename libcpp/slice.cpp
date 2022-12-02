#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


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



// Sort Vector of Pairs
bool sort_by_second(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return (a.second > b.second);
}

bool sort_by_first(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return (a.first > b.first);
}



// Print max key/value of map by value
void max_pair_by_value(std::map<int, int> &maps)
{
    auto ptr = std::max_element
    (
        maps.begin(), maps.end(), 
        [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
            return (a.second < b.second);
            }
        );
    
    std::cout << ptr->first << ' ' << ptr->second;
}