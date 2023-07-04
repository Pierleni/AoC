////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using pt            = std::pair<int,int>;
using Propose       = std::map<pt, std::vector<pt>>;
using vector_str    = std::vector<std::string>;
using vector_int    = std::vector<int>;
using vector_char   = std::vector<char>;
using vector_float  = std::vector<float>;
using matrix_int    = std::vector<vector_int>;

using namespace std;

set<pt> dots;

enum {check = 0, NW=0X01, N=0X02, NE=0X04, W=0X08, E=0X10, SW=0X20, S=0X40, SE=0X80};

pt dir[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0 ,1},{1,-1},{1,0},{1,1}};

pt operator+(const pt &a, const pt &b) {return make_pair(a.first + b.first, a.second + b.second);};

const vector<int> rules[] = 
{   //    0         1  2
    {NW | N | NE , -1, 0},
    {SW | S | SE ,  1, 0},
    {NW | W | SW ,  0,-1},
    {NE | E | SE ,  0, 1},
};

vector_char card {'n','s','w','e'};


void swap(vector_char &card) {
    char temp = card[0];
    card.erase(card.begin());
    card.push_back(temp);
}


auto get_neigh_bitmap(const pt &from) 
{
    auto neighbor = 0, bit = 1;
    for (int i = 0; i < sizeof(dir)/sizeof(dir[0]); i++) {
        if (dots.find(from + dir[i]) != dots.end())
            neighbor |= bit;
        bit <<= 1;
    }
    return neighbor;    
}


int display(set<pt> &dots) 
{
    // find min - max
    int maxY = 0; int minY = INT_MAX;
    int maxX = 0; int minX = INT_MAX;
    for (const pt &d : dots) 
    {
        if (d.first > maxY) maxY = d.first;
        if (d.first < minY) minY = d.first;
        if (d.second > maxX) maxX = d.second;
        if (d.second < minX) minX = d.second;
    }
    // draw it and count
    int count = 0;
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (dots.find(make_pair(y, x)) != dots.end()) 
                cout << '#';
            else {
                cout << '.';
                count++;
            }
        }
        cout << endl;   
    }
    return count; //(maxY - minY + 1) * (maxX - minX + 1) - dots.size();
}


pair<int,int> solve()
{
    pair<int,int> result = {0,0};
    vector<string> file = import_file("input/d23.txt");
    for (int y=0; y<file.size(); ++y) {
        for (int x = 0; x < file[y].size(); x++) {
            if (file[y][x] == '#') 
                dots.insert(make_pair(y, x));
        }
    }
    
    // main loop
    for (int round=0; ; round++)
    {
        //cout << round << endl;
        Propose propose;
        for (const pt &from : dots) 
        {
            auto neighbors = get_neigh_bitmap(from);

            if (neighbors == 0)
                continue;

            for (int i = 0; i < sizeof(rules)/sizeof(rules[0]); i++)
            {
                vector<int> rule = rules[(round + i) % 4];
                //neighbors &= rule[0];
                if ((neighbors & rule[0]) == 0) 
                {
                    pt to = from + make_pair(rule[1], rule[2]);     // rules index
                    propose[to].push_back(from);
                    break;
                }
            }
        }
        // system("cls");
        // cout << display(dots) << '\n';

        bool elf_move = false;
        for (auto &p : propose) 
        {
            if (p.second.size() == 1) 
            {
                dots.insert(p.first);
                dots.erase(dots.find(p.second[0]));
                elf_move = true;
            }
        }
        

        if (round == 9) 
            result.first = display(dots);

        if (!elf_move) {
            result.second = round + 1;
            return result;
        }
    }
    return result;
}

int main()
{
    pair<int,int> result = solve();
    cout << "Part 1: " << result.first << endl;
    cout << "Part 2: " << result.second << endl;
}

