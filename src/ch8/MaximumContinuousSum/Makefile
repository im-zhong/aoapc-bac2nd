all: maximum_continuous_sum.out

CXXFLAGS = -std=c++11 -Wall

maximum_continuous_sum.out: maximum_continuous_sum.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: maximum_continuous_sum.out
	cat in.txt | ./maximum_continuous_sum.out > tmp.txt; \
	diff tmp.txt out.txt