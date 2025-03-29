all: common_subexpression_elimination.out

CXXFLAGS = -std=c++11 -Wall -g

common_subexpression_elimination.out: common_subexpression_elimination.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: common_subexpression_elimination.out
	cat in.txt | ./common_subexpression_elimination.out > tmp.txt; \
	diff tmp.txt out.txt