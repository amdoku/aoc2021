CC?=gcc
CXX?=g++

CXX_FLAGS ?= -std=c++20 -O3 -g -Wall -Wextra -Wpedantic -Wconversion

solution: main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean:
	rm solution
	
