all: bug_feature.out

CXXFLAGS = -std=c++11 -Wall -g

bug_feature.out: bug_feature.cpp
	c++ $(CXXFLAGS) -o $@ $^

solution.out: solution.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: bug_feature.out
	cat in.txt | ./bug_feature.out > tmp.txt; \
	diff tmp.txt out.txt


solution: solution.out
	cat in.txt | ./solution.out > tmp.txt; \
	diff tmp.txt out.txt