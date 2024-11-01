all: binary_search.out

CXXFLAGS = -std=c++11 -Wall 

binary_search.out: binary_search.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: binary_search.out
	cat in.txt | ./binary_search.out > tmp.txt; \
	diff tmp.txt out.txt