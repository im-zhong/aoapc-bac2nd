all: another_crisis.out

CXXFLAGS = -std=c++11 -Wall -g

another_crisis.out: another_crisis.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: another_crisis.out
	cat in.txt | ./another_crisis.out > tmp.txt; \
	diff tmp.txt out.txt