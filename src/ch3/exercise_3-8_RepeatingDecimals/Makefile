all: repeating_decimals.out

CXXFLAGS = -std=c++11 -Wall -g

repeating_decimals.out: repeating_decimals.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: repeating_decimals.out
	cat in.txt | ./repeating_decimals.out > tmp.txt; \
	diff tmp.txt out.txt