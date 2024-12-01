all: tmp.out

CXXFLAGS = -std=c++11 -Wall -g

tmp.out: tmp.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: tmp.out
	cat in.txt | ./tmp.out > tmp.txt; \
	diff tmp.txt out.txt