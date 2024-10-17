all: quadtrees.out

CXXFLAGS = -std=c++11 -Wall -g

quadtrees.out: quadtrees.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: quadtrees.out
	cat in.txt | ./quadtrees.out > tmp.txt; \
	diff tmp.txt out.txt