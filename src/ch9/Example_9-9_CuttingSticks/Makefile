all: cutting_sticks.out

CXXFLAGS = -std=c++11 -Wall -g

cutting_sticks.out: cutting_sticks.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: cutting_sticks.out
	cat in.txt | ./cutting_sticks.out > tmp.txt; \
	diff tmp.txt out.txt