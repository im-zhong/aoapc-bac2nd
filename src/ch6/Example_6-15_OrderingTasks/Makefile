all: ordering_tasks.out

CXXFLAGS = -std=c++11 -Wall -g

ordering_tasks.out: ordering_tasks.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ordering_tasks.out
	cat in.txt | ./ordering_tasks.out > tmp.txt; \
	diff tmp.txt out.txt