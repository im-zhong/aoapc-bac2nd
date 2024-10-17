all: the_falling_leaves.out

CXXFLAGS = -std=c++11 -Wall -g

the_falling_leaves.out: the_falling_leaves.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: the_falling_leaves.out
	cat in.txt | ./the_falling_leaves.out > tmp.txt; \
	diff tmp.txt out.txt