# on command prompt just type:
# python setup.py yyyy dd

import sys
import os

os.system("")   # enable ansi escape code

year = ""
day = ""

###########################################################
#               check valid command
###########################################################

if len(sys.argv) < 3:
    print("\033[33mMissing arguments (aaaa - dd)\033[37m")
    exit()
else:
    year, day = sys.argv[1], sys.argv[2]


###########################################################
#        if not created yet create input txt file
###########################################################

if (os.path.exists(f"{year}\input\d{day}.txt")):
    print(f"\033[33mIl file d{day}.txt è presente nella cartella {year}\input.\033[37m")
else:
    with open(f"{year}\input\d{day}.txt", 'w') as f:
        f.write('')
        

###########################################################
#        if not created yet create .cpp file
###########################################################

if (os.path.exists(f"{year}\d{day}.cpp")):
    print(f"\033[33mIl file d{day}.cpp è presente nella cartella {year}.\033[37m")
else:
    with open(f"{year}\d{day}.cpp", 'w') as f:
        f.write(f"""
#include <iostream>
#include <vector>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using namespace std;
            
int main()
{{
    std::vector<std::string> file = import_file( "input/d{day}.txt" );

    return 0;
}}""")      