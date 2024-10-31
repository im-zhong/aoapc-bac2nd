all: quick_sort.out

CXXFLAGS = -std=c++11 -Wall 

quick_sort.out: quick_sort.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: quick_sort.out
	cat in.txt | ./quick_sort.out > tmp.txt; \
	diff tmp.txt out.txt