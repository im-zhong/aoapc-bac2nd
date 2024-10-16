all: trees_on_the_level.out

CXXFLAGS = -std=c++11 -Wall -g

trees_on_the_level.out: trees_on_the_level.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: trees_on_the_level.out
	cat in.txt | ./trees_on_the_level.out > tmp.txt; \
	diff tmp.txt out.txt