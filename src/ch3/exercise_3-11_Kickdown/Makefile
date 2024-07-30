all: kickdown.out

CXXFLAGS = -std=c++11 -Wall -g

kickdown.out: kickdown.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: kickdown.out
	cat in.txt | ./kickdown.out > tmp.txt; \
	diff tmp.txt out.txt