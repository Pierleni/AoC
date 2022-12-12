#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;

#include <map>


class Monkey
{
    private:
    char operation;
    std::string operation_value;
    int monkey_a;
    int monkey_b;

    public:
    std::deque<unsigned long long int> items;
    int items_inspected = 0;
    int test;

    Monkey(std::deque<unsigned long long int> Items, char op, std::string v, int t, int a, int b)
    {
        items = Items;
        operation = op;
        operation_value = v;
        test = t;
        monkey_a = a;
        monkey_b = b;
    }

    void show_all()
    {
        for (int n : items) { std::cout << n <<' ';}
        prints("\n");

    }

    void inspect(std::vector<Monkey> &monkeys, int part, int lcm)
    {
        while (items.size() > 0)
        {
            unsigned long long int temp;
            unsigned long long int value;
            unsigned long long int item = items[0];   

            if (operation_value == "old") value = item;
            else value = convert_to<unsigned long long int>(operation_value);

            if (operation == '+') temp = item + value;
            else temp = item * value;

            if (part == 1) temp = std::floor(temp / 3);
            else temp %= lcm;

            if (temp % test == 0) monkeys[monkey_a].items.push_back(temp);
            else monkeys[monkey_b].items.push_back(temp);

            items_inspected++;
            items.pop_front();
        }
    }
};


void solve(int part)
{
    vector_str file = import_file("input/d11.txt");
    std::vector<unsigned long long int> monkeys_charts;
    int round = part == 2 ? 10000 : 20;
    std::vector<Monkey> monkeys;
    int lcm = 1;

    for (int i = 0; i < file.size(); i += 7)
    {
        std::deque<unsigned long long int> items;
        char operation;
        std::string operation_value;
        long long test;
        int monkey_a;
        int monkey_b;

        // Parsing items
        vector_str start_items = line_to_words(file[i+1]);
        vector_str items_line = slice_vector(2, start_items.size(), start_items);
        for (std::string word : items_line) {
            replace_char(word, ',', ' ');
            unsigned long long value = convert_to<int>(word);
            items.push_back(value);
        }

        // Parsing operation
        vector_str operations_line = line_to_words(file[i+2]);
        operation = operations_line[operations_line.size() - 2][0];
        operation_value = operations_line[operations_line.size() - 1];

        // Parsing test
        vector_str test_line = line_to_words(file[i+3]);
        test = convert_to<int>(test_line[test_line.size() - 1]);

        // Parsing if
        vector_str if_line_a = line_to_words(file[i+4]);
        vector_str if_line_b = line_to_words(file[i+5]);
        monkey_a = convert_to<int>(if_line_a[if_line_a.size() - 1]);
        monkey_b = convert_to<int>(if_line_b[if_line_b.size() - 1]);

        Monkey monkey = Monkey(items, operation, operation_value, test, monkey_a, monkey_b);
        monkeys.push_back(monkey);            
    }


    // For Part 2  
    for (Monkey m : monkeys) 
        lcm *= m.test;

    for (int r = 0; r < round; r++)
    {
        for (int i = 0; i < monkeys.size(); i++)
        {
            monkeys[i].inspect(monkeys, part, lcm);
        }        
    }

    for (int i = 0; i < monkeys.size(); i++) {
        monkeys_charts.push_back(monkeys[i].items_inspected);
    }
    std::sort(monkeys_charts.rbegin(), monkeys_charts.rend());
    std::cout << "Part " << part << " :"<< monkeys_charts[0] * monkeys_charts[1]<<std::endl; 
}

int main()
{
    solve(1);
    solve(2);
    return 0;
}
