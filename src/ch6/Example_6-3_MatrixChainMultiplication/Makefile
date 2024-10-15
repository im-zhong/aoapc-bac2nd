all: matrix_chain_multiplication.out

CXXFLAGS = -std=c++11 -Wall -g

matrix_chain_multiplication.out: matrix_chain_multiplication.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: matrix_chain_multiplication.out
	cat in.txt | ./matrix_chain_multiplication.out > tmp.txt; \
	diff tmp.txt out.txt