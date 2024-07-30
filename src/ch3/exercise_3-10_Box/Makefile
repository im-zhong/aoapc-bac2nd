all: box.out

CXXFLAGS = -std=c++11 -Wall -g

box.out: box.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: box.out
	cat in.txt | ./box.out > tmp.txt; \
	diff tmp.txt out.txt