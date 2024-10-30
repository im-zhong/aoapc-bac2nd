all: editing_a_book.out

CXXFLAGS = -std=c++11 -Wall -g

editing_a_book.out: editing_a_book.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: editing_a_book.out
	cat in.txt | ./editing_a_book.out > tmp.txt; \
	diff tmp.txt out.txt