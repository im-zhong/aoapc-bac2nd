all: fabled_rooks.out

CXXFLAGS = -std=c++11 -Wall -g

fabled_rooks.out: fabled_rooks.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: fabled_rooks.out
	cat in.txt | ./fabled_rooks.out > tmp.txt; \
	diff tmp.txt out.txt