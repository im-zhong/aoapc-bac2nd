all: a_spy_in_the_metro.out

CXXFLAGS = -std=c++11 -Wall -g

a_spy_in_the_metro.out: a_spy_in_the_metro.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: a_spy_in_the_metro.out
	cat in.txt | ./a_spy_in_the_metro.out > tmp.txt; \
	diff tmp.txt out.txt