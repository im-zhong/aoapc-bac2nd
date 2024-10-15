all: concurrency_simulator.out

CXXFLAGS = -std=c++11 -Wall -g

concurrency_simulator.out: concurrency_simulator.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: concurrency_simulator.out
	cat in.txt | ./concurrency_simulator.out > tmp.txt; \
	diff tmp.txt out.txt