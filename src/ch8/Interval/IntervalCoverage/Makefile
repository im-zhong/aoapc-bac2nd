all: interval_coverage.out

CXXFLAGS = -std=c++11 -Wall -g

interval_coverage.out: interval_coverage.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: interval_coverage.out
	cat in.txt | ./interval_coverage.out > tmp.txt; \
	diff tmp.txt out.txt