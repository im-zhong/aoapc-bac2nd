all: egypt_fraction.out

CXXFLAGS = -std=c++11 -Wall -g

egypt_fraction.out: egypt_fraction.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: egypt_fraction.out
	cat in.txt | ./egypt_fraction.out > tmp.txt; \
	diff tmp.txt out.txt