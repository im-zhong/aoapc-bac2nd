all: colossal_fibonacci_numbers.out

CXXFLAGS = -std=c++11 -Wall -g

colossal_fibonacci_numbers.out: colossal_fibonacci_numbers.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: colossal_fibonacci_numbers.out
	cat in.txt | ./colossal_fibonacci_numbers.out > tmp.txt; \
	diff tmp.txt out.txt