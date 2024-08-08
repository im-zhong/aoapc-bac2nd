all: database.out

CXXFLAGS = -std=c++11 -Wall -g

database.out: database.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: database.out
	cat in.txt | ./database.out > tmp.txt; \
	diff tmp.txt out.txt