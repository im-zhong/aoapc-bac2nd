all: boxes_in_a_line.out

CXXFLAGS = -std=c++11 -Wall -g

boxes_in_a_line.out: boxes_in_a_line.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: boxes_in_a_line.out
	cat in.txt | ./boxes_in_a_line.out > tmp.txt; \
	diff tmp.txt out.txt