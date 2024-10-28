all: answer.out

CXXFLAGS = -std=c++11 -Wall -g

answer.out: answer.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: answer.out
	cat in.txt | ./answer.out > tmp.txt; \
	diff tmp.txt out.txt