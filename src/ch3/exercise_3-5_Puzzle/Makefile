all: puzzle.out

CXXFLAGS = -Wall -g

puzzle.out: puzzle.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: puzzle.out
	cat in.txt | ./puzzle.out > tmp.txt; \
	diff tmp.txt out.txt