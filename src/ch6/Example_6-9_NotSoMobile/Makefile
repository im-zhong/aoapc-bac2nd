all: not_so_mobile.out

CXXFLAGS = -std=c++11 -Wall -g

not_so_mobile.out: not_so_mobile.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: not_so_mobile.out
	cat in.txt | ./not_so_mobile.out > tmp.txt; \
	diff tmp.txt out.txt