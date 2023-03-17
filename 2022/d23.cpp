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

////////////////////////////////////////////////////////////////////////////////////////////////////////////


// #include <algorithm>
// #include <iostream>
// #include <vector>
// #include <map>
// #include <set>

// #include "../libcpp/io.cpp"
// #include "../libcpp/slice.cpp"
// #include "../libcpp/parse.cpp"
// #include "../libcpp/grids.cpp"
// #include "../libcpp/convert.cpp"

// using vector_str    = std::vector<std::string>;
// using vector_int    = std::vector<int>;
// using vector_char   = std::vector<char>;
// using vector_float  = std::vector<float>;
// using matrix_int    = std::vector<vector_int>;
// using pt            = std::pair<int,int>;

// using namespace std;

// pt dir[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0 ,1},{1,-1},{1,0},{1,1}};

// map<char,pt> finalMove {{'n',{-1,0}},{'s',{1,0}},{'w',{0,-1}},{'e',{0,1}}};

// map<char,vector<pt>> directions {
//     {'n',{{-1,0},{-1,-1},{-1,1}}},
//     {'s',{{1,0},{1,-1},{1,1}}},
//     {'w',{{0,-1},{-1,-1},{1,-1}}},
//     {'e',{{0,1},{-1,1},{1,1}}}};

// pt add(pt a, pt b) {return {a.first + b.first, a.second + b.second};}


// bool hasToMove(pt p, const vector<pt> &dots) {
//     int free = 0, neigh = 0;
//     for (int i = 0; i < 8; i++) {
//         pt np = add(p, dir[i]);
//         if (find(dots.begin(), dots.end(), np) != dots.end())
//             return true;
//     }
//     return false;
// }


// pt moveElf(pt origin, vector_char &card, const vector<pt> dots, map<pt,int> &seen) {
//     for (int i = 0; i < 4; i++) {
//         int count = 0;
//         char dir = card[i];
//         for (int j = 0; j < 3; j++) {
//             pt dest = add(origin, directions[dir][j]);
//             if (find(dots.begin(), dots.end(), dest) != dots.end()) {
//                 count++;
//                 j = 3;
//             }
//         }
//         if (!count) // if is free
//         {
//             pt finalDest = add(origin, finalMove[dir]);         // take position
//             if (seen.count(finalDest)) seen[finalDest] += 1;    // update seen map
//             else seen[finalDest] = 1;
//             return finalDest;                                   // return new pos
//         }
//     }
//     return origin;                                              // otherwise return same pos (not moving)
// }



// void tryToMove(vector<pair<pt,pt>> &toMove, vector_char &card, const vector<pt> &dots) {
//     map<pt,int> seen;
//     for (int i = 0; i < toMove.size(); i++) {
//         pt origin = toMove[i].first;
//         toMove[i].second = moveElf(origin, card, dots, seen);
//     }
    
//     for (auto &s : seen) {
//         if (s.second == 2) {
//             pt toErase = s.first;
//             for (auto &p : toMove) {
//                 if (p.second == toErase) p.second = p.first;
//             }
//         }
//     }
// }


// void swap(vector_char &card) {
//     char temp = card[0];
//     card.erase(card.begin());
//     card.push_back(temp);
// }


// void display(vector<pt> &dots) {
//     // find min - max
//     int maxY = 0; int minY = INT_MAX;
//     int maxX = 0; int minX = INT_MAX;
//     for (const pt &d : dots) 
//     {
//         if (d.first > maxY) maxY = d.first;
//         if (d.first < minY) minY = d.first;
//         if (d.second > maxX) maxX = d.second;
//         if (d.second < minX) minX = d.second;
//     }
//     // draw it and count
//     int ans = 0;
//     for (int y = minY; y <= maxY; y++) {
//         for (int x = minX; x <= maxX; x++) {
//             pt dot = {y,x};
//             if (find(dots.begin(), dots.end(), dot) != dots.end()) 
//                 cout << '#';
//             else {
//                 ans++;
//                 cout << '.';
//             }
//         }
//         cout << endl;   
//     }
//     cout << ans << endl;;
// }


// int main()
// {
//     int round = 10;
//     vector<pt> orDots;
//     vector_char card {'n','s','w','e'};
//     vector_str file = import_file("input/d23.txt");
    
//     // initialize dots
//     for (int y = 0; y < file.size(); y++) {
//         for (int x = 0; x < file[y].size(); x++) {
//             if (file[y][x] == '#') orDots.push_back({y, x});
//         }
//     }
    
//     ///////////////// Part 1 /////////////////////
//     vector<pt> dots = orDots;
//     for (int i = 0; i < round; i++)
//     {
//         cout << i << endl;
//         vector<pair<pt,pt>> toMove;
//         vector<pt> defDots;

//         // check if can move
//         for (pt d : dots) 
//         {
//             if (hasToMove(d, dots)) toMove.push_back({d,d});
//             else defDots.push_back(d);
//         }

//         cout << "tick ";
//         // move
//         tryToMove(toMove, card, dots);
        
//         // update dots
//         vector<pt> newDots;
//         for (pt &d : defDots) {newDots.push_back(d);}
//         for (pair<pt,pt> &p : toMove)  {newDots.push_back(p.second);}
//         dots = newDots;
        
//         // swap directions for next round
//         swap(card);
//     }
//     display(dots);


//     ///////////////// Part 2 /////////////////////


//     return 0;
// }
