#include <iostream>
#include <vector>

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

int current = 0;
vector<int> cups;;
vector<int> picked {0,0,0};


void showResult(vector<int> &vec) {
    for (int i=1; i<vec.size(); i++) {cout << vec[i];}
}


bool alreadyPicked(int n, vector<int> picked) {
    return (find(picked.begin(), picked.end(), n) != picked.end());
}


int main()
{
    vector_str file = import_file("input/d23.txt");
    for (char &c : file[0]) {cups.push_back(c - '0');}  // Convert numeric char to int

    for (int move=0; move<100; move++) 
    {
        int curr = (move) % cups.size();
        for (int i=0; i<3; i++) {
            picked[i] = cups[(curr + i + 1) % cups.size()];
            
        }
        
        int landed = cups[curr];
        int nextLand = landed - 1;
        while (alreadyPicked(nextLand, picked) || nextLand < 1) {
            nextLand = (nextLand - 1) > 0 ? nextLand - 1 : cups.size();
        }
        
        // Elimini i 3 picked, li rimetti dove devono stare
        for (int i=0; i<3; i++) {
            auto toErase = find(cups.begin(), cups.end(), picked[i]);
            cups.erase(toErase);
        }

        // Find New Destination
        auto destination = find(cups.begin(), cups.end(), nextLand);
        for (int i=2; i>=0; i--) {
            cups.insert(destination + 1, picked[i]);
        }
        
        int newPos;
        for (int i=0; i<cups.size(); i++) {
            if (cups[i] == landed) newPos = i;
        }
        int diff = newPos - curr;
        
        rotate(cups.begin(), cups.begin() + diff, cups.end());
    }

    vector<int>::iterator it = find(cups.begin(), cups.end(), 1);
    rotate(cups.begin(), cups.begin() + (it - cups.begin()), cups.end());
    showResult(cups);

    return 0;
}
