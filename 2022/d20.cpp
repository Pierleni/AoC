#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using pairs = std::pair<int64_t,int64_t>;

using namespace std;



int64_t getIndex(std::vector<pairs> v, pairs K) {
    int64_t index;
    auto it = std::find(v.begin(),v.end(), K);
    if (it != v.end()) {
        index = it - v.begin();
    }
    return index;
}



void move(vector<pairs> &v, int oldIndex, pairs coppia, int size) {
    auto it = find(v.begin(), v.end(), coppia);
    int64_t value = coppia.second;

    v.erase(v.begin() + oldIndex);

    int64_t k = std::abs(value)  % static_cast<int64_t>(v.size());
    if (value < 0) {
        for (int64_t i = 0; i < k; i++) {
            if (it == v.begin()) it = v.end();
            --it;
        }
        if (it == v.begin()) it = v.end();
    
    } else if (value > 0) {
        for (int64_t i = 0; i < k; i++) {
            if (it == v.end()) it = v.begin();
            ++it;
        }
        if (it == v.end()) it = v.begin();
    }

    int64_t newIndex = it - v.begin();
    v.insert(v.begin() + newIndex, coppia);
}



void mix(vector_int original, int loop, int64_t decription) 
{
    vector<pairs> orig;
    for (int i = 0; i < original.size(); i++) {
        orig.push_back({i, original[i] * decription});
    }
    
    vector<pairs> vec(orig);
    int size = vec.size();

    for (int i = 0; i < loop; i++)
    {
        for (auto &p : orig) {
            int index = getIndex(vec, p);
            move(vec, index, p, size);
        }
    }
    
    int64_t zeroIndx;
    for (int i=0; i<vec.size();i++) {
        if (vec[i].second == 0) zeroIndx = i;
    }

    int64_t a = vec[(zeroIndx + 1000) % vec.size()].second;
    int64_t b = vec[(zeroIndx + 2000) % vec.size()].second;
    int64_t c = vec[(zeroIndx + 3000) % vec.size()].second;
    std::cout << a << ' '<< b << ' '<< c << '\n';
    std::cout << a + b + c << '\n';
}



int main()
{
    vector_int original;
    vector<pairs> orig;
    vector_str file = import_file("input/d20.txt");
    
    for (string &s : file) {
        original.push_back(convert_to<int>(s));
    }

    mix(original, 1, 1);
    mix(original, 10, 811589153);

    return 0;
}
