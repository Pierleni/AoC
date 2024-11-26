#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include "../libcpp/io.cpp"
#include "../libcpp/slice.cpp"
#include "../libcpp/parse.cpp"
#include "../libcpp/grids.cpp"
#include "../libcpp/convert.cpp"

using vector_str = std::vector<std::string>;
using vector_int = std::vector<int>;
using vector_char = std::vector<char>;
using vector_float = std::vector<float>;

using ull = unsigned long long;

using namespace std;

class Device 
{
	public:
	ull key;
	ull loopSize = 0;				// to find
	int mod = 20201227;
	
	Device(const int n) {key = n;}
	
	void findLoopSize() {
		ull value = 1;
		while (value != key) {
			value *= 7;
			value %= mod;
			loopSize++;
		}
	}
	
	ull encryption(ull key) {
		ull value = 1;
		for (int i=0; i<loopSize; i++) {
			value *= key;
			value %= mod;
		}
		return value;
	}
};

            
int main()
{
    vector_str file = import_file( "input/d25.txt" );
	int cardKey = convert_to<int>(file[0]);
    int doorKey = convert_to<int>(file[1]);
	
	Device *card = new Device(cardKey);
	Device *door = new Device(doorKey);
	
	card->findLoopSize();
	door->findLoopSize();
	
	ull a = card->encryption(door->key);
	ull b = door->encryption(card->key);
	
	if (a == b) {
		cout << "Match! " << a << endl;
	}
    return 0;
}