#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
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

	// 01-1
	ssize_t incrementCount = std::count_if(++std::begin(input), std::end(input), [prevVal = *std::begin(input)] (int64_t currVal) mutable -> bool {
			bool reti = currVal > prevVal;
			prevVal = currVal;
			return reti;
	});

	std::cout << "1 - solution: " << incrementCount << '\n';

	// 01-2
	// Ugly AF, bc it is late and I am tired.
	std::vector<int64_t> sums{};
	auto out {std::back_inserter(sums)};
	for(auto idx{0u}; idx < input.size() - 2u; idx++) {
		out = std::accumulate(std::next(std::begin(input), idx), std::next(std::begin(input), idx + 3u), 0l);
		out++;
	}
	ssize_t incrementWindowCount = std::count_if(++std::begin(sums), std::end(sums), [prevVal = *std::begin(sums)] (int64_t currVal) mutable -> bool {
		bool reti = currVal > prevVal;
		prevVal = currVal;
		return reti;
	});

	std::cout << "2 - solution: " << incrementWindowCount << '\n';
	return 0;
}

