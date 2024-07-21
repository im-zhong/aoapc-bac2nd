all: combinatorial_number.out

CXXFLAGS = -std=c++17 -Wall -g

combinatorial_number.out: combinatorial_number.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: combinatorial_number.out
	cat in.txt | ./combinatorial_number.out > tmp.txt; \
	diff tmp.txt out.txt