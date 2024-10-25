all: division.out

CXXFLAGS = -std=c++11 -Wall -g

division.out: division.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: division.out
	cat in.txt | ./division.out > tmp.txt; \
	diff tmp.txt out.txt