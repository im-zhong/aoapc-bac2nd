all: digit_counting.out

CXXFLAGS = -Wall -g

digit_counting.out: digit_counting.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: digit_counting.out
	cat in.txt | ./digit_counting.out > tmp.txt; \
	diff tmp.txt out.txt