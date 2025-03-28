all: unrooted_tree_to_rooted_tree.out

CXXFLAGS = -std=c++11 -Wall -g

unrooted_tree_to_rooted_tree.out: unrooted_tree_to_rooted_tree.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: unrooted_tree_to_rooted_tree.out
	cat in.txt | ./unrooted_tree_to_rooted_tree.out > tmp.txt; \
	diff tmp.txt out.txt