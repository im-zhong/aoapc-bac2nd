all: dictionary.out

CXXFLAGS = -std=c++11 -Wall -g

dictionary.out: dictionary.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: dictionary.out
	cat in.txt | ./dictionary.out > tmp.txt; \
	diff tmp.txt out.txt