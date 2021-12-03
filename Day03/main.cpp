#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <bitset>

#include <utilities.hpp>
#include <array>
#include <ranges>
#include <limits>

constexpr size_t BitCount = 12;
using BinaryNumber = std::bitset<BitCount>;

template<size_t BitCount>
BinaryNumber solution1(std::istream_iterator<util::read_sep<BinaryNumber, '\n'>> start) {
	decltype(start) end{};

	// if elem < 0 => 0 are more common
	// if elem > 0 => 1 are more common
	std::array<int, BitCount> bitCount{};

	std::for_each(start, end, [&bitCount] (BinaryNumber const & elem) -> void {
		for(std::weakly_incrementable auto idx : std::views::iota(0u, BitCount)) {
			if (elem.test(idx)) { bitCount[idx]++; }
			else { bitCount[idx]--; }
		}
	});

	BinaryNumber gammarate{};
	std::for_each(bitCount.begin(), bitCount.end(), [&gammarate, idx = 0u](int elem) mutable -> void {
		gammarate.set(idx, elem > 0);
		idx++;
	});

	return gammarate;
}

template<size_t BitCount>
size_t solution2(std::istream_iterator<util::read_sep<BinaryNumber, '\n'>> start, BinaryNumber const & commonBits) {
	decltype(start) end{};
	(void) commonBits;

	return 0ull;
}

template<size_t N>
consteval size_t generate_mask() {
	static_assert(std::numeric_limits<size_t>::digits >= N, "paranoia");
	static_assert(N >= 1,"paranoia");

	size_t reti{1};
	for(std::weakly_incrementable auto idx : std::views::iota(1u, N)) {
		reti |= (1 << idx);
	}

	return reti;
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

	std::istream_iterator<util::read_sep<BinaryNumber, '\n'>> start{inFile};

	BinaryNumber const gammaValue = solution1<BitCount>(start);
	size_t const lifeSupportRating = solution2<BitCount>(start, gammaValue);

	size_t const MASK = generate_mask<BitCount>();

	std::cout << "Solution 1: " << gammaValue.to_ulong() * (MASK & ~(gammaValue.to_ulong())) << '\n';
	std::cout << "Solution 2: " << lifeSupportRating << '\n';

	return 0;
}

