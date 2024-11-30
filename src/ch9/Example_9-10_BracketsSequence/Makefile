all: brackets_sequence.out

CXXFLAGS = -std=c++11 -Wall -g

brackets_sequence.out: brackets_sequence.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: brackets_sequence.out
	cat in.txt | ./brackets_sequence.out > tmp.txt; \
	diff tmp.txt out.txt