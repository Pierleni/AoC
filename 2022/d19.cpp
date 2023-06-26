#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <map>
#include <set>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using namespace std;

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

enum {ORE, CLAY, OBSI, GEOD};

struct  Elements {
    int ore;
    int clay;
    int obsi;
    int geod;
};


struct Blueprint {
    int ID;
    Elements inventario {0,0,0,0};
    Elements robots {1,0,0,0};
    std::vector<Elements> costs{{},{},{},{}};
};


std::vector<Blueprint> parse_input(vector_str &file) {
    std::vector<Blueprint> blueprints;
    for (std::string lines : file) {
        Blueprint blue;

        vector_str line = line_to_words(lines);
        blue.ID = convert_to<int>(return_replace_char(line[1], ':', ' '));
        blue.costs[ORE].ore     = convert_to<int>(line[6]);
        blue.costs[CLAY].ore    = convert_to<int>(line[12]);
        blue.costs[OBSI].ore    = convert_to<int>(line[18]);
        blue.costs[OBSI].clay   = convert_to<int>(line[21]);
        blue.costs[GEOD].ore    = convert_to<int>(line[27]);
        blue.costs[GEOD].obsi   = convert_to<int>(line[30]);
        
        blueprints.push_back(blue);
    }
    return blueprints;
}

int bfs(Blueprint &BP, int T)
{
    int best = 0;
    deque<tuple<int,int,int,int,int,int,int,int,int>> que;
    set<tuple<int,int,int,int,int,int,int,int,int>> seen;
    que.push_back(make_tuple(0,0,0,0,1,0,0,0,T));

    while (!que.empty())
    {
        tuple<int,int,int,int,int,int,int,int,int> state = que.front();
        int ore,clay,obsi,geod,rore,rclay,robsi,rgeod,t;
        std::tie(ore,clay,obsi,geod,rore,rclay,robsi,rgeod,t) = state;
        que.pop_front();

        best = std::max(best, geod);

        if (t==0) 
            continue;

        int Core = std::max(BP.costs[ORE].ore, std::max(BP.costs[CLAY].ore, std::max(BP.costs[OBSI].ore, BP.costs[GEOD].ore)));

        rore = std::min(rore, Core);
        rclay = std::min(rclay, BP.costs[OBSI].clay);
        robsi = std::min(robsi, BP.costs[GEOD].obsi);
        ore = std::min(ore, t * Core - rore * (t-1));
        clay = std::min(clay, t * BP.costs[OBSI].clay - rclay * (t-1));
        obsi = std::min(obsi, t * BP.costs[GEOD].obsi - robsi * (t-1));

        state = make_tuple(ore,clay,obsi,geod,rore,rclay,robsi,rgeod,t);

        if (seen.count(state))
            continue;
        
        seen.insert(state);
        
        // Try doing nothing
        que.push_back(make_tuple(ore+rore, clay+rclay, obsi+robsi, geod+rgeod, rore, rclay, robsi, rgeod, t-1));
        // And roing something
        if (ore >= BP.costs[ORE].ore)
            que.push_back(make_tuple(ore - BP.costs[ORE].ore + rore, clay+rclay, obsi+robsi, geod+rgeod, rore+1, rclay, robsi, rgeod, t-1));
        if (ore >= BP.costs[CLAY].ore)
            que.push_back(make_tuple(ore - BP.costs[CLAY].ore + rore, clay+rclay, obsi+robsi, geod+rgeod, rore, rclay+1, robsi, rgeod, t-1));
        if ((ore >= BP.costs[OBSI].ore) && (clay >= BP.costs[OBSI].clay))
            que.push_back(make_tuple(ore - BP.costs[OBSI].ore + rore, clay - BP.costs[OBSI].clay + rclay, obsi+robsi, geod+rgeod, rore, rclay, robsi+1, rgeod, t-1));
        if ((ore >= BP.costs[GEOD].ore) && (obsi >= BP.costs[GEOD].obsi))
            que.push_back(make_tuple(ore - BP.costs[GEOD].ore + rore, clay+rclay, obsi - BP.costs[GEOD].obsi + robsi, geod+rgeod,rore,rclay, robsi, rgeod+1, t-1));
    }
    return best;
}



int main()
{
    vector_str file = import_file("input/d19.txt");
    std::vector<Blueprint> blueprints = parse_input(file);
    int part1 = 0;
    int part2 = 1;
    
    for (auto &b : blueprints) {
        int solve = bfs(b, 24);
        part1 += solve * b.ID;   
    }
    cout << "Part 1: " << part1 << std::endl;

    for (int i=0; i<3; i++) {
        Blueprint b = blueprints[i];
        int solve = bfs(b,32);
        part2 *= solve;
    }
    cout << "Part 2: " << part2 << std::endl;

    return 0;
}