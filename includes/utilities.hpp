//
// Created by cn on 01.12.20.
//

#ifndef AOS2020_SAMPLE_UTILITIES_HPP
#define AOS2020_SAMPLE_UTILITIES_HPP

#include <istream>
#include <iterator>
#include <ranges>
#include <limits>

namespace util {

	// comma seperated template code from: https://stackoverflow.com/a/21838123
	template<class T, char sep = ','>
	struct read_sep { //type used for temporary input
		T t; //where data is temporarily read to
		operator const T &() const { return t; } //acts like an int in most cases
	};

	template<class T, char sep>
	std::istream &operator>>(std::istream &in, read_sep<T, sep> &t) {
		if (!(in >> t.t)) //if we failed to read the int
			return in; //return failure state
		if (in.peek() == sep) //if next character is a comma
			in.ignore(); //extract it from the stream and we're done
		else //if the next character is anything else
			in.clear(); //clear the EOF state, read was successful
		return in; //return
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
}
#endif //AOS2020_SAMPLE_UTILITIES_HPP
