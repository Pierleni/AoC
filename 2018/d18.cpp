#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using ll = long long;

int H, W;

/*
In particular:

'.' An open acre will become filled with trees if three or more adjacent acres contained trees. Otherwise, nothing happens.

'|' An acre filled with trees will become a lumberyard if three or more adjacent acres were lumberyards. Otherwise, nothing happens.

'#' An acre containing a lumberyard will remain a lumberyard if it was adjacent to at least one other lumberyard and at least one acre containing trees. Otherwise, it becomes open.
*/

enum status {
    open,
    tree,
    lumberyard
};


bool checkNewPoint(const std::pair<int,int> &p) {
    return ((0 <= p.first ) && (p.first < H) && (0 <= p.second) && (p.second < W));
}


std::pair<int,int> add(std::pair<int,int> a, std::pair<int,int> b) {
    return {a.first + b.first, a.second + b.second};
}

void display(std::vector<std::vector<int>> &n_matrix) {
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            switch (n_matrix[y][x]) 
            {
                case status::open:
                std::cout << '.';
                break;

                case status::tree:
                std::cout << '|';
                break;

                case status::lumberyard:
                std::cout << '#';
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool reOpen(std::vector<std::vector<int>> &matrix, int y, int x) {
    bool t=false; bool l=false;
    static constexpr std::pair<int,int> dirs[] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for (int i=0; i<8; i++) {
        std::pair<int,int> np = add({y,x}, dirs[i]); 
        if (checkNewPoint(np) && matrix[np.first][np.second] == status::tree) {
            t = true;
        }
        if (checkNewPoint(np) && matrix[np.first][np.second] == status::lumberyard) {
            l = true;
        }
    }
    return ((t) && (l));
}

void countNeigh(std::vector<std::vector<int>> &matrix, int y, int x, int kind, int &count) {
    static constexpr std::pair<int,int> dirs[] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for (int i=0; i<8; i++) {
        std::pair<int,int> np = add({y,x}, dirs[i]); 
        if (checkNewPoint(np) && matrix[np.first][np.second] == kind) {
            count++;
        }
    }
}

void swapMatrix(std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &n_matrix) 
{
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            int count = 0;
            
            if (matrix[y][x] == status::open) {
                countNeigh(matrix, y, x, status::tree, count);
                if (count >= 3) n_matrix[y][x] = status::tree;
            }

            else if (matrix[y][x] == status::tree) {
                countNeigh(matrix, y, x, status::lumberyard, count);
                if (count >= 3) n_matrix[y][x] = status::lumberyard;
            }

            else if (matrix[y][x] == status::lumberyard) {
                if (!reOpen(matrix, y, x)) n_matrix[y][x] = status::open;
            }
        } 
    }
    
}

int countAcres(const std::vector<std::vector<int>> &n_matrix) {
    int tree = 0;
    int lumber = 0;
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            if (n_matrix[y][x] == status::tree) tree++;
            else if (n_matrix[y][x] == status::lumberyard) lumber++;
        }
    }
    //std::cout << tree << ' ' << lumber << '\n';
    return tree * lumber;
}

std::vector<std::vector<int>> generate(std::vector<std::string> &file) {
    H = file.size();
    W = file[0].size();

    std::vector<std::vector<int>> matrix;
    for (int y=0; y<H; y++) {
        std::vector<int> v;
        matrix.push_back(v);
        for (int x=0; x<W; x++) {
            char c = file[y][x];
            switch (c) {
                case '.':
                matrix.back().push_back(0);
                break;

                case '|':
                matrix.back().push_back(1);
                break;

                case '#':
                matrix.back().push_back(2);
                break;
            }
        }
    }
    return matrix;
}


int main()
{
    std::vector<std::string> file = import_file("input/d18.txt");
    std::vector<std::vector<int>> matrix = generate(file);
    std::vector<std::vector<int>> n_matrix = matrix;
    
    ////////////////////////// Part1    
    for (int i=0; i<10; i++) {
        swapMatrix(matrix, n_matrix);
        matrix = n_matrix;
        //display(n_matrix);
    }
    std::cout << "Part 1: "<<countAcres(n_matrix) << '\n';


    ////////////////////////// Part2
    matrix = generate(file);
    n_matrix = matrix;

    ll T = 1000000000LL;
    std::map<std::vector<std::vector<int>>, ll> track;
    for (int t=0; t<T; t++) {
        swapMatrix(matrix, n_matrix);
        matrix = n_matrix;

        if (track.count(n_matrix) == 1) {
            ll skip = (T - t) / (t - track[n_matrix]);
            t += skip * (t - track[n_matrix]);
        } else {track[n_matrix] = t;}
    }
    std::cout << "Part 2: "<<countAcres(n_matrix) << '\n';

    return 0;
}