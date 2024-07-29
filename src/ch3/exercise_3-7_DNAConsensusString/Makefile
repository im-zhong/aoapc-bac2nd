all: dna_consensus_string.out

CXXFLAGS = -std=c++11 -Wall -g

dna_consensus_string.out: dna_consensus_string.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: dna_consensus_string.out
	cat in.txt | ./dna_consensus_string.out > tmp.txt; \
	diff tmp.txt out.txt