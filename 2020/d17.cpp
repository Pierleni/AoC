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

int CYCLES = 6;

int solve_p1(std::set<std::tuple<int,int,int>> &active);
int solve_p2(std::set<std::tuple<int,int,int,int>> &active2);

using namespace std;

int main()
{
    vector_str file = import_file("input/d17.txt");
    
    std::set<std::tuple<int,int,int>> active;

    for (int y = 0; y < file.size(); y++)
    {
        for (int x = 0; x < file[y].size(); x++)
        {
            if (file[y][x] == '#') 
            {
                active.insert(std::make_tuple(y, x, 0));
            }
        }
    }

    cout << "Part 1: " << solve_p1(active);  


    // Part 2
    std::set<std::tuple<int,int,int,int>> active2;

    for (int y = 0; y < file.size(); y++)
    {
        for (int x = 0; x < file[y].size(); x++)
        {
            if (file[y][x] == '#') 
            {
                active2.insert(std::make_tuple(y, x, 0, 0));
            }
        }
    }
    
    cout << "Part 2: " << solve_p2(active2);  
  

    return 0;
}


int solve_p1(std::set<std::tuple<int,int,int>> &active)
{
    for (int c = 0; c < CYCLES; c++)
    {
        std::set<std::tuple<int,int,int>> news;

        int maxY = 0, maxX = maxY, maxZ = maxY;
        int minY = INT32_MAX, minX = minY, minZ = minY;

        for (auto a : active)
        {
            if (get<0>(a) > maxY) maxY = get<0>(a);
            if (get<0>(a) < minY) minY = get<0>(a);
            if (get<1>(a) > maxX) maxX = get<1>(a);
            if (get<1>(a) < minX) minX = get<1>(a);
            if (get<2>(a) > maxZ) maxZ = get<2>(a);
            if (get<2>(a) < minZ) minZ = get<2>(a);

        }
        
        for (int y=minY-1; y<maxY+2; y++)
        {
            for (int x=minX-1; x<maxX+2; x++) 
            {
                for (int z=minZ-1; z<maxZ+2; z++)
                {
                    // check for neigbors
                    int neigb = 0;
                    
                    for (int dy=-1; dy<2; dy++)         
                    {
                        for (int dx=-1; dx<2; dx++) 
                        {
                            for (int dz=-1; dz<2; dz++) 
                            {
                                if (dy != 0 || dx != 0 || dz != 0)
                                {
                                    std::tuple<int,int,int> npt = {y+dy, x+dx, z+dz};
                                    
                                    if (std::find(active.begin(), active.end(), npt) != active.end()) 
                                    {
                                        neigb += 1;
                                    }
                                }
                            }
                        }
                    }
                    // if is active
                    std::tuple<int,int,int> curr = {y,x,z};
                    if (std::find(active.begin(), active.end(), curr) != active.end())
                    {
                        if (neigb == 2 || neigb == 3) 
                        {
                            news.insert(curr);
                        }
                    }
                    // if not active
                    if (std::find(active.begin(), active.end(), curr) == active.end())
                    {
                        if (neigb == 3)
                        {
                            news.insert(curr);
                        }
                    }
                }
            }
        }
        active = news;
    }

    return active.size();
}


int solve_p2(std::set<std::tuple<int,int,int,int>> &active)
{
    for (int c = 0; c < CYCLES; c++)
    {
        std::set<std::tuple<int,int,int,int>> news;

        int maxY = 0, maxX = maxY, maxZ = maxY, maxW = maxY;
        int minY = INT32_MAX, minX = minY, minZ = minY, minW = minY;

        for (auto a : active)
        {
            if (get<0>(a) > maxY) maxY = get<0>(a);
            if (get<0>(a) < minY) minY = get<0>(a);
            if (get<1>(a) > maxX) maxX = get<1>(a);
            if (get<1>(a) < minX) minX = get<1>(a);
            if (get<2>(a) > maxZ) maxZ = get<2>(a);
            if (get<2>(a) < minZ) minZ = get<2>(a);
            if (get<3>(a) > maxW) maxW = get<3>(a);
            if (get<3>(a) < minW) minW = get<3>(a);

        }
        
        for (int y=minY-1; y<maxY+2; y++)
        {
            for (int x=minX-1; x<maxX+2; x++) 
            {
                for (int z=minZ-1; z<maxZ+2; z++)
                {
                    for (int w=minW-1; w<maxW+2; w++)
                    {
                        // check for neigbors
                        int neigb = 0;
                        
                        for (int dy=-1; dy<2; dy++)         
                        {
                            for (int dx=-1; dx<2; dx++) 
                            {
                                for (int dz=-1; dz<2; dz++) 
                                {
                                    for (int dw=-1; dw<2; dw++)
                                    {
                                        if (dy != 0 || dx != 0 || dz != 0 || dw != 0)
                                        {
                                            std::tuple<int,int,int,int> npt = {y+dy, x+dx, z+dz, w+dw};
                                            
                                            if (std::find(active.begin(), active.end(), npt) != active.end()) 
                                            {
                                                neigb += 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // if is active
                        std::tuple<int,int,int,int> curr = {y,x,z,w};

                        if (std::find(active.begin(), active.end(), curr) != active.end())
                        {
                            if (neigb == 2 || neigb == 3) 
                            {
                                news.insert(curr);
                            }
                        }
                        // if not active
                        if (std::find(active.begin(), active.end(), curr) == active.end())
                        {
                            if (neigb == 3)
                            {
                                news.insert(curr);
                            }
                        }
                    }
                }
            }
        }
        active = news;
    }

    return active.size();
}