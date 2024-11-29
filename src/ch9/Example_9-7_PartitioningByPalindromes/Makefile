all: partitioning_by_palindromes.out

CXXFLAGS = -std=c++11 -Wall -g

partitioning_by_palindromes.out: partitioning_by_palindromes.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: partitioning_by_palindromes.out
	cat in.txt | ./partitioning_by_palindromes.out > tmp.txt; \
	diff tmp.txt out.txt