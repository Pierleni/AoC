#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

#define DEBUG

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


Elements operator+(const Elements &inv, const Elements &rob) {
    return {inv.ore + rob.ore, inv.clay + rob.clay,
            inv.obsi + rob.obsi, inv.geod + rob.geod};
}

Elements operator-(const Elements &inv, const Elements &cost) {
    return {inv.ore - cost.ore, inv.clay - cost.clay,
            inv.obsi - cost.obsi, inv.geod - cost.geod};
}

bool operator>=(const Elements &inv, const Elements &cost) {
    return ((inv.ore >= cost.ore) && (inv.clay >= cost.clay) &&
           (inv.obsi >= cost.obsi) && (inv.geod >= cost.geod));
}

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

void collecting(Blueprint &b) {
    b.inventario = (b.robots + b.inventario);
}

void try_to_spend(Blueprint &b) {
    for (int elem=ORE; elem<=4; elem++) {
        std::cout << elem << '\n';
        if ( b.inventario >= b.costs[elem] ) {
            b.inventario = ( b.inventario - b.costs[elem] );
            switch (elem)
            {
                case ORE:   b.robots.ore  += 1; break;
                case CLAY:  b.robots.clay += 1; break;
                case OBSI:  b.robots.obsi += 1; break;
                case GEOD:  b.robots.geod += 1; break;
            }
        }
    }
}

int main()
{
    vector_str file = import_file("input/d19.txt");
    std::vector<Blueprint> blueprints = parse_input(file);
    
    for (auto &b : blueprints) {
        for (int t=1; t<=24; t++) {

            // Spend
            try_to_spend(b);

            // Collect
            //collecting(b);

            ////////////////////// Debug ///////////////////
            #ifdef DEBUG
                std::cout << "\n== MINUTE " << t << " ==\n";
                std::cout << "ID: " << b.ID << "\nCosts:\n";
                for (auto e : b.costs) 
                {
                    std::cout << 
                        e.ore << ' ' << 
                        e.clay << ' ' <<
                        e.obsi << ' ' <<
                        e.geod << '\n';
                }
                std::cout << '\n';

                std::cout << "Inventario:\n" << 
                    b.inventario.ore << ' ' <<
                    b.inventario.clay << ' ' <<
                    b.inventario.obsi << ' ' <<
                    b.inventario.geod << '\n';      
                std::cout << "Robots:\n" << 
                    b.robots.ore << ' ' <<
                    b.robots.clay << ' ' <<
                    b.robots.obsi << ' ' <<
                    b.robots.geod << '\n';   
            std::getchar();
            #endif
            
        }
    
    }


    
  

    return 0;
}
