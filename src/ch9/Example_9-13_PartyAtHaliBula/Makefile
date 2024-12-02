all: party_at_hali_bula.out

CXXFLAGS = -std=c++11 -Wall -g

party_at_hali_bula.out: party_at_hali_bula.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: party_at_hali_bula.out
	cat in.txt | ./party_at_hali_bula.out > tmp.txt; \
	diff tmp.txt out.txt