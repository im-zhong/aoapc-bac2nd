all: Krypton_factor.out

CXXFLAGS = -std=c++11 -Wall -g

Krypton_factor.out: Krypton_factor.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: Krypton_factor.out
	cat in.txt | ./Krypton_factor.out > tmp.txt; \
	diff tmp.txt out.txt