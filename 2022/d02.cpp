#include <iostream>
#include <sstream>
#include <fstream>
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

#include <map>

enum RPS 
{
    ROCK        = 1,
    PAPER       = 2,
    SCISSORS    = 3, 
};


std::string winner(int op, int pl)
{
    if (op == pl) return "draw";
    else if (pl == 1 && op == 3) return "win";
    else if (pl == 3 && op == 2) return "win";
    else if (pl == 2 && op == 1) return "win";
    else return "loose";
}


int main()
{
    vector_str file = import_file("input/d02.txt");
    //show_content(file);

    std::map<char, int> opponent;
    opponent.insert(std::make_pair('A', ROCK));
    opponent.insert(std::make_pair('B', PAPER));
    opponent.insert(std::make_pair('C', SCISSORS));

    std::map<char, int> player;
    player.insert(std::make_pair('X', ROCK));
    player.insert(std::make_pair('Y', PAPER));
    player.insert(std::make_pair('Z', SCISSORS));

    std::map<char, std::string> needs;
    needs.insert(std::make_pair('X', "loose"));
    needs.insert(std::make_pair('Y', "draw"));
    needs.insert(std::make_pair('Z', "win"));
    
    char op, pl;
    int total_score_p1 = 0;
    int total_score_p2 = 0;
    
    for (std::string riga : file) 
    {
        op = riga[0];
        pl = riga[2];

        // Part 1
        if (winner(opponent[op], player[pl]) == "win") {
            total_score_p1 += player[pl] + 6;
        }
        if (winner(opponent[op], player[pl]) == "draw") {
            total_score_p1 += player[pl] + 3;
        }
        else if (winner(opponent[op], player[pl]) == "loose") {
            total_score_p1 += player[pl];
        }
        
        // Part 2
        for (size_t choose = ROCK; choose < SCISSORS + 1; choose++)
        {
            if (winner(opponent[op], choose) == needs[pl]) {
                if (needs[pl] == "win") total_score_p2 += choose + 6;
                else if (needs[pl] == "loose") total_score_p2 += choose;
                else if (needs[pl] == "draw") total_score_p2 += choose + 3;
                break;
            }
        }
    }
    std::cout << "Part 1: " << total_score_p1 << std::endl;
    std::cout << "Part 2: " << total_score_p2;
    return 0;
}