#include <iostream>
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

std::vector<int64_t> input;

struct cup
{
    int64_t value;
    cup *next { nullptr };
};


int main()
{
    int lo = 1;
    int64_t hi = 1e6;
    int64_t rounds = 10e6;

    std::vector<std::string> file = import_file("input/d23.txt");
    for (char &c : file[0]) input.push_back(c - '0');
    
    std::vector<cup> cups(1e6);
    std::vector<cup*> index(1e6 + 1);   // Zero value doesn't exist on input
    std::vector<int64_t> picked(3);

    // Populate Vectors
    for (int64_t i=0; i<hi; i++) {
        int64_t n = i < input.size() ? input[i] : i+1;

        cups[i] = { n, nullptr };
        index[cups[i].value] = &cups[i];

        if (i > 0) cups[i - 1].next = &cups[i];
    }
    cups.back().next = &cups[0];

    cup *pos = &cups[0], *q = nullptr, *dest = nullptr;
    for (int64_t r=0; r<rounds; r++) 
    {
        q = pos->next;

        picked[0] = q->value; q = q->next;
        picked[1] = q->value; q = q->next;
        picked[2] = q->value;

        int64_t n = pos->value; n = --n < lo ? hi : n;
        while (std::find(picked.begin(), picked.end(), n) != picked.end()) {
            n = --n < lo ? hi : n;
        }
        dest = index[n];

        cup *tmp = q->next; 
        q->next = dest->next;
        dest->next = pos->next;
        
        pos->next = tmp;
        pos = pos->next;
    }

    cup *x = index[1];
    std::cout << x->next->value << ' ' << x->next->next->value << std::endl;
    std::cout << x->next->value * x->next->next->value;

    return 0;
}