all: minimum_sum_lcm_1.out

CXXFLAGS = -std=c++11 -Wall -g

minimum_sum_lcm_1.out: minimum_sum_lcm_1.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: minimum_sum_lcm_1.out
	cat in.txt | ./minimum_sum_lcm_1.out > tmp.txt; \
	diff tmp.txt out.txt