all: quick_selection.out

CXXFLAGS = -std=c++11 -Wall 

quick_selection.out: quick_selection.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: quick_selection.out
	cat in.txt | ./quick_selection.out > tmp.txt; \
	diff tmp.txt out.txt