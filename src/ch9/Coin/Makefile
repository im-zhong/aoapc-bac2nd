all: coin.out

CXXFLAGS = -std=c++11 -Wall -g

coin.out: coin.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: coin.out
	cat in.txt | ./coin.out > tmp.txt; \
	diff tmp.txt out.txt