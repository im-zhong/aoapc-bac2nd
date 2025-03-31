all: calling_circles.out

CXXFLAGS = -std=c++11 -Wall -g

calling_circles.out: calling_circles.cpp
	c++ $(CXXFLAGS) -o $@ $^

solution.out: solution.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: calling_circles.out
	cat in.txt | ./calling_circles.out > tmp.txt; \
	diff tmp.txt out.txt


solution: solution.out
	cat in.txt | ./solution.out > tmp.txt; \
	diff tmp.txt out.txt