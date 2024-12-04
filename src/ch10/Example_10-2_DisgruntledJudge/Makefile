all: disgruntled_judge.out

CXXFLAGS = -std=c++11 -Wall -g

disgruntled_judge.out: disgruntled_judge.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: disgruntled_judge.out
	cat in.txt | ./disgruntled_judge.out > tmp.txt; \
	diff tmp.txt out.txt