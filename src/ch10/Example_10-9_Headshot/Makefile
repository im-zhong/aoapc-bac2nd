all: headshot.out

CXXFLAGS = -std=c++11 -Wall -g

headshot.out: headshot.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: headshot.out
	cat in.txt | ./headshot.out > tmp.txt; \
	diff tmp.txt out.txt