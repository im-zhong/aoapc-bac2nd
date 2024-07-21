all: circular_sequence.out

CXXFLAGS = -Wall -g

circular_sequence.out: circular_sequence.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: circular_sequence.out
	cat in.txt | ./circular_sequence.out > tmp.txt; \
	diff tmp.txt out.txt