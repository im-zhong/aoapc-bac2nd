all: unique_snowflakes_2.out

CXXFLAGS = -std=c++11 -Wall -g

unique_snowflakes_2.out: unique_snowflakes_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: unique_snowflakes_2.out
	cat in.txt | ./unique_snowflakes_2.out > tmp.txt; \
	diff tmp.txt out.txt