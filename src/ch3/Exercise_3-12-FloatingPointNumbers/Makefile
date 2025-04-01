all: floating_point_numbers.out

CXXFLAGS = -std=c++11 -Wall -g

floating_point_numbers.out: floating_point_numbers.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: floating_point_numbers.out
	cat in.txt | ./floating_point_numbers.out > tmp.txt; \
	diff tmp.txt out.txt