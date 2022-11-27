#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>


class Device
{
    private:
        std::string opcode;
        int a, b, c;

        enum Opcode 
        {
            addi,
            addr,
            muli,
            mulr,
            bani,
            banr,
            bori,
            borr,
            seti,
            setr,
            gtir,
            gtri,
            gtrr,
            eqir,
            eqri,
            eqrr
        };

        enum Opcode convertOp(std::string op) 
        {
            if ( op == "addi") return addi;
            else if ( op == "addr") return addr;
            else if ( op == "muli") return muli;
            else if ( op == "mulr") return mulr;
            else if ( op == "bani") return bani;
            else if ( op == "banr") return banr;
            else if ( op == "bori") return bori;
            else if ( op == "borr") return borr;
            else if ( op == "seti") return seti;
            else if ( op == "setr") return setr;
            else if ( op == "gtir") return gtir;
            else if ( op == "gtri") return gtri;
            else if ( op == "gtrr") return gtrr;
            else if ( op == "eqir") return eqir;
            else if ( op == "eqri") return eqri;
            else return eqrr;
        }
    
    public:
        int mem[6];
        unsigned int ptr;
        std::vector<std::string> rom;

        void LoadRom(std::string fileName)
        {
            std::string line;
            std::stringstream ss;
            std::ifstream myfile(fileName);
            if (myfile.is_open())
            {
                while (std::getline(myfile, line)) {
                    rom.push_back(line);                /* fill the mem */
                }
            }
            myfile.close();                             /* close it */

            std::string temp;
            ss << rom[0];                               /* take first line */
            ss >> temp >> ptr;
            rom.erase(rom.begin());                     /* and pop it from rom */

        }

        void Run(int index=0)
        {
            mem[0] = index;
            while (mem[ptr] < (signed)rom.size())
            {
                std::string instr = rom[mem[ptr]];
                std::stringstream ss(instr);
                ss >> opcode >> a >> b >> c;
                //std::cout << opcode << ' ' << ' ' << a << ' ' << b << ' ' << c << '\n';
                
                switch (convertOp(opcode))
                {
                    case addi:
                        mem[c] = mem[a] + b;
                        break;

                    case addr:
                        mem[c] = mem[a] + mem[b];
                        break;

                    case muli:
                        mem[c] = mem[a] * b;
                        break;

                    case mulr:
                        mem[c] = mem[a] * mem[b];
                        break;

                    case bani:
                        mem[c] = mem[a] & b;
                        break;

                    case banr:
                        mem[c] = mem[a] & mem[b];
                        break;

                    case bori:
                        mem[c] = mem[a] | b;
                        break;

                    case borr:
                        mem[c] = mem[a] | mem[b];
                        break;

                    case seti:
                        mem[c] = a;
                        break;

                    case setr:
                        mem[c] = mem[a];
                        break;

                    case gtir:
                        if (a > mem[b]) mem[c] = 1;
                        else mem[c] = 0;
                        break;

                    case gtri:
                        if (mem[a] > b) mem[c] = 1;
                        else mem[c] = 0;
                        break;

                    case gtrr:
                        if (mem[a] > mem[b]) mem[c] = 1;
                        else mem[c] = 0;
                        break;

                    case eqir:
                        if (a == mem[b]) mem[c] = 1;
                        else mem[c] = 0;
                        break;
                    
                    case eqri:
                        if (mem[a] == b) mem[c] = 1;
                        else mem[c] = 0;
                        break;
                    
                    case eqrr:
                        if (mem[a] == mem[b]) mem[c] = 1;
                        else mem[c] = 0;
                        break;
                    
                    default:
                        break;
                }
                //displayMem();
                //std::getchar();
                mem[ptr]++;
            }

            std::cout << "Register 0 at " << mem[0] << std::endl; 
        }

        void displayMem(){
            for (int n : mem) {
                std::cout << n << ' ';
            }
        }

};




int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::string path = "input/d19.txt";
    Device device = Device();
    device.LoadRom(path);

    device.Run();  
    auto stop_time = std::chrono::high_resolution_clock::now();
    std::cout << "Time in cpp: " << (stop_time - start_time).count() << std::endl;  

    return 0;
}