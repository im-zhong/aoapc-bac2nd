all: cows_and_cars.out

CXXFLAGS = -std=c++11 -Wall -g

cows_and_cars.out: cows_and_cars.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: cows_and_cars.out
	cat in.txt | ./cows_and_cars.out > tmp.txt; \
	diff tmp.txt out.txt