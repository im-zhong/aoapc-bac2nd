all: marble.out

CXXFLAGS = -std=c++11 -Wall -g

marble.out: marble.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: marble.out
	cat in.txt | ./marble.out > tmp.txt; \
	diff tmp.txt out.txt