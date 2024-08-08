all: ugly_numbers.out

CXXFLAGS = -std=c++11 -Wall -g

ugly_numbers.out: ugly_numbers.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ugly_numbers.out
	./ugly_numbers.out > tmp.txt