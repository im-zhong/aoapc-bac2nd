all: four_values_whose_sum_is_zero.out

CXXFLAGS = -std=c++11 -Wall -g

four_values_whose_sum_is_zero.out: four_values_whose_sum_is_zero.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: four_values_whose_sum_is_zero.out
	cat in.txt | ./four_values_whose_sum_is_zero.out > tmp.txt; \
	diff tmp.txt out.txt