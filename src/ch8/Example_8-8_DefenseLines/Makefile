all: defense_lines_2.out

CXXFLAGS = -std=c++11 -Wall -g

defense_lines_2.out: defense_lines_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: defense_lines_2.out
	cat in.txt | ./defense_lines_2.out > tmp.txt; \
	diff tmp.txt out.txt