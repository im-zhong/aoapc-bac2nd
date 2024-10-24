all: abbotts_revenge.out

CXXFLAGS = -std=c++11 -Wall -g

abbotts_revenge.out: abbotts_revenge.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: abbotts_revenge.out
	cat in.txt | ./abbotts_revenge.out > tmp.txt; \
	diff tmp.txt out.txt