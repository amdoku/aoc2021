#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include <utilities.hpp>

struct Submarine {
	int64_t depth{};
	int64_t horizontal{};
};

enum class Direction {
	UP,
	DOWN,
	FORWARD
};

struct SubCommand {
	Direction dir;
	int64_t value;
};

std::istream & operator>>(std::istream & in, SubCommand &sub) {
	std::string input;
	in >> input >> sub.value;

	if (input == "down") {
		sub.dir = Direction::DOWN;
	} else if (input == "up") {
		sub.dir = Direction::UP;
	} else if (input == "forward") {
		sub.dir = Direction::FORWARD;
	}
	return in;
}

void handle(Submarine & sub, SubCommand const & input) {
	switch(input.dir) {
		case Direction::DOWN:
			sub.depth += input.value;
			break;
		case Direction::UP:
			sub.depth -= input.value;
			break;
		case Direction::FORWARD:
			sub.horizontal += input.value;
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
	std::istream_iterator<util::read_sep<SubCommand, '\n'>> start{inFile};
	decltype(start) end{};

	Submarine sub{};
	std::for_each(start, end, [&sub](SubCommand const & input) {
		handle(sub, input);
	});

	std::cout << "Solution 1: " << sub.depth * sub.horizontal;

	return 0;
}

