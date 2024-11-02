all: pair_of_reversed_order.out

CXXFLAGS = -std=c++11 -Wall -g

pair_of_reversed_order.out: pair_of_reversed_order.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: pair_of_reversed_order.out
	cat in.txt | ./pair_of_reversed_order.out > tmp.txt; \
	diff tmp.txt out.txt