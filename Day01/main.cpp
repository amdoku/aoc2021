#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <utilities.hpp>

int main(int argc, char ** argv) {
	if (argc != 2) {
		printf("Expected usage: %s <input file>\n", argv[0]);
		return -1;
	}
	std::ifstream inFile{argv[1]};
	if (!inFile) {
		std::cout << "Error opening file. Exiting\n";
		return -1;
	}
	std::istream_iterator<util::read_sep<int64_t, '\n'>> start{inFile};
	decltype(start) end{};

	std::vector<int64_t> const input{start, end};

	ssize_t incrementCount = std::count_if(++std::begin(input), std::end(input), [prevVal = *std::begin(input)] (int64_t currVal) mutable -> bool {
			bool reti = currVal > prevVal;
			prevVal = currVal;
			return reti;
	});

	std::cout << "1 - solution: " << incrementCount << '\n';
	
	return 0;
}

