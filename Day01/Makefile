CC?=gcc
CXX?=g++

I_DIRS=../includes

CXX_FLAGS ?= -std=c++20 -O3 -g -Wall -Wextra -Wpedantic -Wconversion -I$(I_DIRS)

bin/solution: main.cpp
	mkdir -p bin
	$(CXX) $(CXX_FLAGS) -o $@ $<

run: bin/solution
	bin/solution input

clean:
	rm bin/*

