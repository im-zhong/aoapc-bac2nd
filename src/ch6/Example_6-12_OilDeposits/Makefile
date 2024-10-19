all: oil_deposits.out

CXXFLAGS = -std=c++11 -Wall -g

oil_deposits.out: oil_deposits.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: oil_deposits.out
	cat in.txt | ./oil_deposits.out > tmp.txt; \
	diff tmp.txt out.txt