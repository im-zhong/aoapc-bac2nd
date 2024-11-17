all: average.out

CXXFLAGS = -std=c++11 -Wall -g

average.out: average.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: average.out
	cat in.txt | ./average.out > tmp.txt; \
	diff tmp.txt out.txt