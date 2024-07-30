all: all_in_all.out

CXXFLAGS = -std=c++11 -Wall -g

all_in_all.out: all_in_all.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: all_in_all.out
	cat in.txt | ./all_in_all.out > tmp.txt; \
	diff tmp.txt out.txt