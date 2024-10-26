all: bandwidth.out

CXXFLAGS = -std=c++11 -Wall -g

bandwidth.out: bandwidth.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: bandwidth.out
	cat in.txt | ./bandwidth.out > tmp.txt; \
	diff tmp.txt out.txt