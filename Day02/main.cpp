#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#include <utilities.hpp>

struct Submarine {
	uint64_t depth{};
	int64_t horizontal{};
};

void handle(Submarine & sub, std::string const & input) {
	if (std::starts_with(input, "down")) {
		// sub.depth += value;
	} else if (std::starts_with(input, "up")) {
		// sub.depth -= value;
	} else if (std::starts_with(input, "forward")) {
		// sub.horizontal += value;
	} else {
		std::cout << "Unkown command :'" << input << "'\n";
	}
}

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
	std::istream_iterator<util::read_sep<std::string, '\n'>> start{inFile};
	decltype(start) end{};

	Submarine sub{};
	std::for_each(start, end, [&sub](std::string const & input) {
		handle(sub, input);
	});

	std::cout << "Solution 1: " << sub.depth * sub.horizontal;

	return 0;
}

