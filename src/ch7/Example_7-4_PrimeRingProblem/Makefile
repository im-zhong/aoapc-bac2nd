all: prime_ring_problem.out

CXXFLAGS = -std=c++11 -Wall -g

prime_ring_problem.out: prime_ring_problem.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: prime_ring_problem.out
	cat in.txt | ./prime_ring_problem.out > tmp.txt; \
	diff tmp.txt out.txt