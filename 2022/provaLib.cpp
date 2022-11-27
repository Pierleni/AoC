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


struct COORD
{
    int X,Y; 
};


class Star
{
    private:
    COORD vel;

    public:
    COORD pos;

    Star(int x, int y, int vx, int vy)
    {
        pos.X = x;
        pos.Y = y;
        vel.X = vx;
        vel.Y = vy;
    }

    void move()
    {
        pos.Y = (pos.Y + vel.Y);
        pos.X = (pos.X + vel.X);
    }
};



int main()
{
    vector_str file = import_file("input/d00.txt");
    std::vector<std::pair<int,int>> position;
    std::vector<std::pair<int,int>> velocity;

    std::vector<std::vector<char>> matrix;
    
    std::vector<Star> stars;


    vector_int allX;
    vector_int allY;

    int maxX, minX, maxY, minY;

    for (auto f : file) {
        replace_char(f, '<', ' ');
        replace_char(f, '>', ' ');
        replace_char(f, ',', ' ');
        vector_str words = line_to_words(f);

        int x = convert_to<int>(words[1]);
        int y = convert_to<int>(words[2]);
        int vx = convert_to<int>(words[4]);
        int vy = convert_to<int>(words[5]);

        allX.push_back(x);
        allY.push_back(y);

        position.push_back(std::make_pair(x, y));
        velocity.push_back(std::make_pair(vx, vy));

        Star star = Star(x, y, vx, vy);
        stars.push_back(star);
        
    }

    int MIN_X = find_min(allX);
    int MAX_X = find_max(allX);
    int MIN_Y = find_min(allY);
    int MAX_Y = find_max(allY);
    std::cout << MIN_Y <<std::endl;
    std::cout << MIN_X <<std::endl;


    std::cout << '\n';

    int t = 0;
    while (t < 5) {
        matrix = make_matrix2D<char>(30,30,'.');
        for (auto &s : stars) {
            s.move();
            matrix[s.pos.Y + std::abs(MIN_X)][s.pos.X + std::abs(MIN_Y)] = '#';
        }
        t++;
        show_matrix(matrix);
        std::getchar();
    }
    

    return 0;
}
