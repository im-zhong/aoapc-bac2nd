all: stacks_of_flapjacks.out

CXXFLAGS = -std=c++11 -Wall -g

stacks_of_flapjacks.out: stacks_of_flapjacks.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: stacks_of_flapjacks.out
	cat in.txt | ./stacks_of_flapjacks.out > tmp.txt; \
	diff tmp.txt out.txt