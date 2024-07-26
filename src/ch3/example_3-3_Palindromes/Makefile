all: palindromes.out

CXXFLAGS = -Wall -g

palindromes.out: palindromes.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: palindromes.out
	cat in.txt | ./palindromes.out > tmp.txt; \
	diff tmp.txt out.txt