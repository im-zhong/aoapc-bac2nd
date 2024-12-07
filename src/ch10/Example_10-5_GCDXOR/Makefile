all: gcd_xor_1.out

CXXFLAGS = -std=c++11 -Wall -O3

gcd_xor_1.out: gcd_xor_1.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: gcd_xor_1.out
	cat in.txt | ./gcd_xor_1.out > tmp.txt; \
	diff tmp.txt out.txt