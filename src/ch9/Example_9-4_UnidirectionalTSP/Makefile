all: unidirectional_tsp.out

CXXFLAGS = -std=c++11 -Wall -g

unidirectional_tsp.out: unidirectional_tsp.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: unidirectional_tsp.out
	cat in.txt | ./unidirectional_tsp.out > tmp.txt; \
	diff tmp.txt out.txt