all: tree.out

CXXFLAGS = -std=c++11 -Wall -g

tree.out: tree.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: tree.out
	cat in.txt | ./tree.out > tmp.txt; \
	diff tmp.txt out.txt