all: master_mind_hints.out

CXXFLAGS = -Wall -g

master_mind_hints.out: master_mind_hints.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: master_mind_hints.out
	cat in.txt | ./master_mind_hints.out > tmp.txt; \
	diff tmp.txt out.txt