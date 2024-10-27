all: mobile_computing.out

CXXFLAGS = -std=c++11 -Wall -g

mobile_computing.out: mobile_computing.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: mobile_computing.out
	cat in.txt | ./mobile_computing.out > tmp.txt; \
	diff tmp.txt out.txt