all: blocks.out

CXXFLAGS = -std=c++11 -Wall -g

blocks.out: blocks.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: blocks.out
	cat in.txt | ./blocks.out > tmp.txt; \
	diff tmp.txt out.txt