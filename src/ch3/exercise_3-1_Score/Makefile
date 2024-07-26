all: score.out

CXXFLAGS = -Wall -g

score.out: score.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: score.out
	cat in.txt | ./score.out > tmp.txt; \
	diff tmp.txt out.txt