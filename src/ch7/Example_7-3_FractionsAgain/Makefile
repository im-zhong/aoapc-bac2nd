all: fractions_again.out

CXXFLAGS = -std=c++11 -Wall -g

fractions_again.out: fractions_again.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: fractions_again.out
	cat in.txt | ./fractions_again.out > tmp.txt; \
	diff tmp.txt out.txt