all: the_letter_carriers_rounds.out

CXXFLAGS = -std=c++11 -Wall -g

the_letter_carriers_rounds.out: the_letter_carriers_rounds.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: the_letter_carriers_rounds.out
	cat in.txt | ./the_letter_carriers_rounds.out > tmp.txt; \
	diff tmp.txt out.txt