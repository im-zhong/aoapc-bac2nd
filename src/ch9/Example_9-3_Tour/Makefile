all: tour.out

CXXFLAGS = -std=c++11 -Wall -g

tour.out: tour.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: tour.out
	cat in.txt | ./tour.out > tmp.txt; \
	diff tmp.txt out.txt