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

using namespace std;

long long generation = 20;
std::set<long long> plants;

void show_generation(std::set<long long> &p) {
    int max = *p.rbegin() + (- *p.begin());
    cout << max << endl;
    std::string line = "";
    for (int x=0; x<=max; x++) {
        if (p.count(x - *p.begin()))
            line += '#';
        else line += '.';
    }
    cout << line << endl;
}

int main()
{
    std::vector<std::string> file = import_file("input/d12.txt");
    std::vector<std::string> first_line = line_to_words(file[0]);
    std::map<std::string, char> dict;
    long long lower, higher;
    long long start, end;

    std::string initial_state = first_line[2];

    // Popolate Set of Plants
    for (int x = 0; x < initial_state.size(); x++) {
        if (initial_state[x] == '#')
            plants.insert(x);
    }
    // Find the lower/higer point
    lower = *plants.begin();
    higher = *plants.rbegin();

    // Popolate dictionary
    for (int y = 2; y < file.size(); y++) {
        std::vector<std::string> line = line_to_words(file[y]);
        dict[line[0]] = line[2][0];
    }

    show_generation(plants);

    // main loop
    for (long long g=0; g<generation; g++)
    {
        start = lower - 2;
        end = higher + 4;

        std::set<long long> tmp;
        for (int x=start; x<=end; x++) {                // actual point
            std::string line;
            for (int j=-2; j<=2; j++) {                 // neighbours
                int p = x + j;
                line += plants.count(p) ? '#' : '.';
            }
            // check dictionary and save point on temporary set
            if (dict.find(line) != dict.end()) {
                if (dict[line] == '#')
                    tmp.insert(x);
            }
        }
        plants = tmp;
        show_generation(plants);
        getchar();

        lower = *plants.begin();
        higher = *plants.rbegin();
    }

    int result = 0;
    for (int n : plants) {
        result += n;
    }

    cout << result << endl;
    

    return 0;
}