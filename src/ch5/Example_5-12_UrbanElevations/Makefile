all: urban_elevations.out

CXXFLAGS = -std=c++11 -Wall -g

urban_elevations.out: urban_elevations.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: urban_elevations.out
	cat in.txt | ./urban_elevations.out > tmp.txt; \
	diff tmp.txt out.txt