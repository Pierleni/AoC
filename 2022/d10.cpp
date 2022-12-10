#include <iostream>
#include <vector>

#include "../libcpp/io.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;


class Device
{
    private:
    std::vector<std::vector<char>> lcd;
    vector_int signals;
    vector_str file;
    int registers;
    int cycle;
    int busy;
    int row;
    
    int signals_sum()
    {
        int result = 0;
        for (int n : signals) { result += n; }
        return result;
    }

    void check_signal()
    {
        switch (cycle)
        {
            case 20: case 60: case 100: case 140: case 180: case 220:
            signals.push_back(registers * cycle);
            break;

            case 41: case 81: case 121: case 161: case 201:
            row++;
            break;
        }
    }

    void draw_lcd() 
    {
        int crt_position = (cycle % 40) - 1;
        if ((crt_position == registers -1) || (crt_position == registers) || (crt_position == registers + 1))
            lcd[row][crt_position] = '#';
    }

    public:
    Device() 
    {
        file = import_file("input/d10.txt");
        registers = 1;
        cycle = 1;
        busy = 0;
        row = 0;

        // Initialize LCD
        for (int y = 0; y < 6; y++)
        {
            std::vector<char> line;

            for (int x = 0; x < 40; x++) 
            {
                line.push_back('.');
            }
            lcd.push_back(line);
        }        
    }

    void run()
    {
        for (std::string line : file) 
        {
            vector_str instr = line_to_words(line);
            std::string opcode = instr[0];
            
            if (opcode == "noop") 
            {
                cycle++;

                check_signal();

                draw_lcd();
            }
            else 
            {
                busy = 2;
                int value = convert_to<int>(instr[1]);
                
                while (busy) 
                {
                    cycle++;

                    if ((busy % 2 == 1)) registers += value;

                    check_signal();
                    
                    draw_lcd();
                    
                    busy--;
                }
            }
        }
        std::cout << "Parte 1: " << signals_sum() << std::endl;
        std::cout << "Parte 2: " << std::endl;
        show_matrix(lcd);
    }
};


int main()
{
    Device device = Device();
    device.run();
    return 0;
}