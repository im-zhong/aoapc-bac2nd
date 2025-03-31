all: audiophobia.out

CXXFLAGS = -std=c++11 -Wall -g

audiophobia.out: audiophobia.cpp
	c++ $(CXXFLAGS) -o $@ $^

solution.out: solution.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: audiophobia.out
	cat in.txt | ./audiophobia.out > tmp.txt; \
	diff tmp.txt out.txt


solution: solution.out
	cat in.txt | ./solution.out > tmp.txt; \
	diff tmp.txt out.txt