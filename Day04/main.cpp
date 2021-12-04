#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <bitset>
#include <sstream>

#include <utilities.hpp>
#include <array>

class BingoCard {
	std::array<int, 25> values{0};
	std::bitset<25> ticked{};
	bool isDone{false};
public:
	BingoCard() = default;
	explicit BingoCard(std::array<int, 25> val) noexcept : values(val) {
	}

	BingoCard(BingoCard const &) noexcept = default;
	BingoCard(BingoCard&&) noexcept = default;

	BingoCard& operator=(BingoCard const&) noexcept = default;
	BingoCard& operator=(BingoCard &&) noexcept = default;

	[[nodiscard]] bool accept(int number) noexcept {
		if (isDone) return false;
		auto begin{std::cbegin(values)};
		auto end{std::cend(values)};
		auto needle = std::find(begin, end, number);
		if (needle != end) {
			ticked.set(static_cast<size_t>(std::distance(begin, needle)));
		}

		return (isDone = hasRow() || hasCol());
	}

	[[nodiscard]] int sumOfUnmarkedNumbers() const noexcept {
		int sum{0u};
		for(auto idx = 0u; idx < values.max_size(); idx++) {
			if (!ticked.test(idx)) {
				sum += values[idx];
			}
		}
		return sum;
	}

private:
	[[nodiscard]] bool hasRow() const noexcept {
		size_t const pattern = ticked.to_ullong();
		for(auto shift = 0x1Fu; shift < (1 << 25); shift = shift << 5) {
			if ((pattern & shift) == shift) {
				return true;
			}
		}
		return false;
	}

	[[nodiscard]] bool hasCol() const noexcept {
		size_t const pattern = ticked.to_ullong();
		for(auto shift = 1u | (1 << 5) | (1 << 10) | (1 << 15) | (1 << 20); shift < (1 << 25); shift = shift << 1) {
			if ((pattern & shift) == shift) {
				return true;
			}
		}
		return false;
	}
};

std::istream& operator>>(std::istream & in, BingoCard & card) {
	std::array<int, 25> vals{};
	for(auto idx{0u}; in && idx < vals.max_size(); idx++) {
		in >> vals[idx];
	}

	if (in) {
		card = BingoCard(vals);
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

	// extract first line, bc they contain the drawn numbers in order
	std::string input{};
	inFile >> input;
	std::istringstream is{input};
	std::istream_iterator<util::read_sep<int, ','>> drawnNumbers{is};

	std::vector<int> const inputNumbers{drawnNumbers, decltype(drawnNumbers){}};

	std::istream_iterator<util::read_sep<BingoCard, '\n'>> start{inFile};
	std::vector<BingoCard> cards{start, decltype(start){}};

	std::optional<int> sol1{};
	std::optional<int> sol2{};
	for(auto number = std::cbegin(inputNumbers); number < std::cend(inputNumbers); number++) {
		for(auto card = std::begin(cards); card < std::end(cards); card++) {
			if (card->accept(*number)) {
				if (!sol1.has_value()) {
					sol1 = card->sumOfUnmarkedNumbers() * (*number);
				}
				sol2 = card->sumOfUnmarkedNumbers() * (*number);
			}
		}
	}

	std::cout << "Solution 1: " << sol1.value_or(-1) << '\n';
	std::cout << "Solution 2: " << sol2.value_or(-1) << '\n';

	return 0;
}

