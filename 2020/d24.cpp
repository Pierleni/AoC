
#include <iostream>
#include <vector>
#include <tuple>
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

using tuple3 = std::tuple<int,int,int>;

/*
    to work with exagons, theorize three axes:   z/\y
    x = orizontal                               x|  |x
    y, z = vertical diagonals                    y\/z
*/

int days = 100;
int x, y, z = 0;
std::set<tuple3> blackTiles;

tuple3 operator+(const tuple3 &a, const tuple3 &b) {
    return {std::get<0>(a) + std::get<0>(b),
	        std::get<1>(a) + std::get<1>(b),
	        std::get<2>(a) + std::get<2>(b)};
}

void checkHorizontal(char c) {
    switch (c)
    {
        case 'e':
        x += 2;y += 1;z += 1;
        break;

        case 'w':
        x -= 2;y -= 1;z -= 1;
        break;
    }
}

void checkDiagonals(std::string c) {
    if (c == "ne") {x += 1;y += 1;} 
    else if (c == "se") {x += 1;z += 1;}
    else if (c == "sw") {x -= 1;y -= 1;}
    else if (c == "nw") {x -= 1;z -= 1;}
}
            
int main()
{
    vector_str file = import_file( "input/d24.txt" );
    for (string &line : file) 
    {
        x=0; y=0; z=0;
        int index = 0;
        while (index < line.size()) 
        {
            if (line[index] == 'e' || line[index] == 'w') {
                checkHorizontal(line[index]);
                index++;
            } else {
                checkDiagonals(line.substr(index, 2));
                index += 2;
            }
        }

        tuple3 tmp = {x, y, z};
        if (blackTiles.count(tmp)) {blackTiles.erase(tmp);} else {blackTiles.insert(tmp);}
    }

    cout << "Part 1: " << blackTiles.size() << endl;

    /////////////////////// P A R T 2 /////////////////////////

    std::set<tuple3> tilesCopy = blackTiles;

    for (int d=0; d<days; d++) 
    {
        std::set<tuple3> allTiles = blackTiles;
        tuple3 dir[] = {
			{2,1,1},{-2,-1,-1},{-1,-1,0},{1,1,0},{1,0,1},{-1,0,-1}};
        
        // find all adjacents
		for (auto tile : blackTiles) {
			for (int i=0; i<6; i++) {
				tuple3 tmpTile = tile + dir[i];
				allTiles.insert(tmpTile);
			}
		}
		// game of life
		for (auto tile : allTiles) {
			// is black
			if (blackTiles.count(tile)) {
				int adjacent = 0;
				for (int i=0; i<6; i++) {
					tuple3 tmpTile = tile + dir[i];
					if (blackTiles.count(tmpTile)) adjacent++;
				}
				if (adjacent == 0 || adjacent > 2) tilesCopy.erase(tile);
			}
			// is white
			else {
				int adjacent = 0;
				for (int i=0; i<6; i++) {
					tuple3 tmpTile = tile + dir[i];
					if (blackTiles.count(tmpTile)) adjacent++;
				}
				if (adjacent == 2) tilesCopy.insert(tile);
			}
		}
        blackTiles = tilesCopy;

    }
    cout << "Part 2: " << blackTiles.size() << endl;


    return 0;
}