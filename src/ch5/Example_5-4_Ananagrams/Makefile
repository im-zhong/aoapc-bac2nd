all: ananagrams.out

CXXFLAGS = -std=c++11 -Wall -g

ananagrams.out: ananagrams.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ananagrams.out
	cat in.txt | ./ananagrams.out > tmp.txt; \
	diff tmp.txt out.txt