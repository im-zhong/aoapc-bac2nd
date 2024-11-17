all: defense_lines.out

CXXFLAGS = -std=c++11 -Wall -g

defense_lines.out: defense_lines.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: defense_lines.out
	cat in.txt | ./defense_lines.out > tmp.txt; \
	diff tmp.txt out.txt