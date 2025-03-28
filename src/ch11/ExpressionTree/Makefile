all: expression_tree.out

CXXFLAGS = -std=c++11 -Wall -g

expression_tree.out: expression_tree.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: expression_tree.out
	cat in.txt | ./expression_tree.out > tmp.txt; \
	diff tmp.txt out.txt