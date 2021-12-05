#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <bitset>

#include <utilities.hpp>

struct Coordinates {
	uint32_t x;
	uint32_t y;
};

bool operator==(Coordinates const & lhs, Coordinates const & rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Line {
	Coordinates start{};
	Coordinates end{};
};

std::istream & operator>>(std::istream & in, Line & l) {
	char ignored;
	uint32_t x_1, x_2;
	uint32_t y_1, y_2;

	in >> x_1; // number
	in >> ignored; // ,
	in >> y_1; // number
	in >> ignored; // -
	in >> ignored; // >
	in >> x_2; // number
	in >> ignored; // ,
	in >> y_2; // number

	if (in) {
		l.start = {.x = x_1, .y = y_1};
		l.end = {.x = x_2, .y = y_2 };
	}

	return in;
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

	std::istream_iterator<util::read_sep<Line, '\n'>>input {inFile};

	std::vector<Line> const data{input, decltype(input){}};
	uint32_t maxX{};
	uint32_t maxY{};

	std::for_each(data.cbegin(), data.cend(), [&maxX, &maxY](Line const & line) -> void {
		maxX = std::max({maxX, line.start.x, line.end.x});
		maxY = std::max({maxY, line.start.y, line.end.y});
	});
	std::vector<int> board((maxX + 1) * (maxY + 1));

	std::for_each(data.begin(), data.end(), [&board, maxX](Line const & line) -> void {
		// only vertical or horizontal lines
		if (line.start.x == line.end.x) {
			int32_t const delta = line.start.y > line.end.y ? -1 : 1;
			Coordinates temp{line.start};
			while(temp != line.end) {
				board.at(temp.x + maxX * temp.y) += 1;
				temp.y = static_cast<uint32_t>(static_cast<int32_t>(temp.y) + delta);
			}
			board.at(line.end.x + maxX * line.end.y) += 1;
		} else if(line.start.y == line.end.y) {
			int const delta = line.start.x > line.end.x ? -1 : 1;
			Coordinates temp{line.start};
			while(temp != line.end) {
				board.at(temp.x + maxX * temp.y) += 1;
				temp.x = static_cast<uint32_t>(static_cast<int32_t>(temp.x) + delta);
			}
			board.at(line.end.x + maxX * line.end.y) += 1;
		} else {
			int const deltaX = line.start.x > line.end.x ? -1 : 1;
			int const deltaY = line.start.y > line.end.y ? -1 : 1;
			Coordinates temp{line.start};
			while(temp != line.end) {
				board.at(temp.x + maxX * temp.y) += 1;
				temp.x = static_cast<uint32_t>(static_cast<int32_t>(temp.x) + deltaX);
				temp.y = static_cast<uint32_t>(static_cast<int32_t>(temp.y) + deltaY);
			}
			board.at(temp.x + maxX * temp.y) += 1;
		}
	});

	/*
	std::for_each(board.cbegin(), board.cend(), [counter = 0u](int const overlap) mutable -> void {
		if (overlap == 0) std::cout << '.';
		else std::cout << overlap;
		counter++;
		if (counter == 10) {
			counter = 0;
			std::cout << '\n';
		}
	});
	//*/

	std::cout << "Solution 1: " << std::count_if(board.cbegin(), board.cend(), [](int const overlap) -> bool {
		return overlap >= 2;
	}) << '\n';

	return 0;
}

