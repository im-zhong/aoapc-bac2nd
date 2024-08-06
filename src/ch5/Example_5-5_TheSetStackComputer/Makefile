all: stack.out

CXXFLAGS = -std=c++11 -Wall -g

stack.out: stack.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: stack.out
	cat in.txt | ./stack.out > tmp.txt; \
	diff tmp.txt out.txt