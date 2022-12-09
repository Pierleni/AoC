#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

enum diagonals 
{
  U,D,L,R,
  UL,UR,DL,DR,
  ULL,URR,DLL,DRR, 
  dUL,dUR,dDL,dDR
};

struct Pos 
{
  int Y;
  int X;
};


int find_head(Pos head, Pos tale);
int solve(int size);


int main()
{
    std::cout << "Part 1: " << solve(2) << std::endl;
    std::cout << "Part 2: " << solve(10);
}


int find_head(Pos head, Pos tale) 
{
    std::vector<std::pair<int, int>> possible_spot = 
        {{-2,0},{2,0},{0,-2},{0,2},                 // U D L R
            {-2,-1},{-2,1},{2,-1},{2,1},            // UL UR DL DR
                {-1,-2},{-1,2},{1,-2},{1,2},        // ULL URR DLL DRR
                    {-2,-2},{-2,2},{2,-2},{2,2}};   // dUL dUR dDL dDR
    for (int i=0; i<possible_spot.size(); i++) {
        int hy = tale.Y + possible_spot[i].first;
        int hx = tale.X + possible_spot[i].second;
        if ((hy == head.Y) && (hx == head.X)) return i;
    }
    return 99;   
}


int solve(int size)
{
    Pos start = {0,0};
    int rope_size = size;
    std::vector<Pos> rope;

    for (int i = 0; i < rope_size; i++) rope.push_back(start);

    std::set<std::pair<int, int>> positions = {{0,0}};
    std::map<char, std::pair<int, int>> directions = 
        {{'U', {-1,0}},{'D', {1,0}},{'L', {0,-1}},{'R', {0,1}}};
    
    vector_str file = import_file("input/d09.txt");

    for (size_t i = 0; i < file.size(); i++)
    {
        vector_str line = line_to_words(file[i]);
        char d = line[0][0]; 
        int step = convert_to<int>(line[1]);

        for (size_t n = 0; n < step; n++)
        {
            rope[0].Y += directions[d].first;
            rope[0].X += directions[d].second;

            for (int j = 1; j < rope_size; j++)
            {
                Pos head = rope[j-1];
                Pos tale = rope[j];

                switch (find_head(head, tale))
                {
                    case UL: case ULL: case dUL:
                        rope[j].Y--;
                        rope[j].X--;
                        break;
                    case UR: case URR: case dUR:
                        rope[j].Y--;
                        rope[j].X++;
                        break;
                    case DL: case DLL: case dDL:
                        rope[j].Y++;
                        rope[j].X--;
                        break;
                    case DR: case DRR: case dDR:
                        rope[j].Y++;
                        rope[j].X++;
                        break;
                    case U:
                        rope[j].Y--;
                        break;
                    case D:
                        rope[j].Y++;
                        break;
                    case L:
                        rope[j].X--;
                        break;    
                    case R:
                        rope[j].X++;
                        break;
                    defalut:
                        break;
                }
            }
            Pos t = rope[rope_size-1];
            positions.insert(std::make_pair(t.Y, t.X));
        }
    }
    return positions.size();
}