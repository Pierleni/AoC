#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using cubes = std::tuple<int, int, int>;

#include <set>


bool evaporate(cubes cube, std::set<cubes> all_cubes) {
    std::deque<cubes> queue;
    std::set<cubes> seen;
    queue.push_back(cube);
    while (!queue.empty()) {
        auto [xx, yy, zz] = queue.front();
        queue.pop_front();
        
        if (seen.count({xx, yy, zz}))       // in seen
            continue;     
        
        if (all_cubes.count({xx,yy,zz}))    // in all cubes
            continue;  
        
        seen.insert({xx,yy,zz});
        if (queue.size() > 5000)            // too far
            return true;   
        
        static constexpr int cor[] = {1, -1};
        for (int i = 0; i < 2; i++) {
            queue.push_back({xx + cor[i], yy, zz});
            queue.push_back({xx, yy + cor[i], zz});
            queue.push_back({xx, yy, zz + cor[i]});
        }
    }
    return false;
}


int main()
{
    std::set<cubes> all_cubes;
    vector_str file = import_file("input/d18.txt");
    for (std::string line : file) {
        vector_str coords = parse_line_byChar(line, ',');
        int x = convert_to<int>(coords[0]);
        int y = convert_to<int>(coords[1]);
        int z = convert_to<int>(coords[2]);
        all_cubes.insert({x, y, z});
    }

    // Part 1
    int ans = 0;
    int edges = 0;
    for (auto cube : all_cubes) {
        edges += 6;
        int xx = std::get<0>(cube);
        int yy = std::get<1>(cube);
        int zz = std::get<2>(cube);

        if (all_cubes.count({xx+1, yy, zz})) ans++;
        if (all_cubes.count({xx-1, yy, zz})) ans++;
        if (all_cubes.count({xx, yy+1, zz})) ans++;
        if (all_cubes.count({xx, yy-1, zz})) ans++;
        if (all_cubes.count({xx, yy, zz+1})) ans++;
        if (all_cubes.count({xx, yy, zz-1})) ans++;  
    }
    std::cout <<"Part 1: "<<edges - ans<<'\n';

    // Part 2
    int ans2 = 0;
    for (auto cube : all_cubes) {
        int xx = std::get<0>(cube);
        int yy = std::get<1>(cube);
        int zz = std::get<2>(cube);

        if (!evaporate({xx+1, yy, zz}, all_cubes)) ans2++;
        if (!evaporate({xx-1, yy, zz}, all_cubes)) ans2++;
        if (!evaporate({xx, yy+1, zz}, all_cubes)) ans2++;
        if (!evaporate({xx, yy-1, zz}, all_cubes)) ans2++;
        if (!evaporate({xx, yy, zz+1}, all_cubes)) ans2++;
        if (!evaporate({xx, yy, zz-1}, all_cubes)) ans2++;
    }
    std::cout << "part 2: " << edges - ans2;

    return 0;
}
