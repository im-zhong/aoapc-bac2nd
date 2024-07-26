all: wertyu.out

CXXFLAGS = -Wall -g

wertyu.out: wertyu.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: wertyu.out
	cat in.txt | ./wertyu.out > tmp.txt; \
	diff tmp.txt out.txt