all: probability_given.out

CXXFLAGS = -std=c++11 -Wall -g

probability_given.out: probability_given.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: probability_given.out
	cat in.txt | ./probability_given.out > tmp.txt; \
	diff tmp.txt out.txt