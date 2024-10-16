all: dropping_balls_2.out

CXXFLAGS = -std=c++11 -Wall -g

dropping_balls_2.out: dropping_balls_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: dropping_balls_2.out
	cat in.txt | ./dropping_balls_2.out > tmp.txt; \
	diff tmp.txt out.txt