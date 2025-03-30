all: slim_span.out

CXXFLAGS = -std=c++11 -Wall -g

slim_span.out: slim_span.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: slim_span.out
	cat in.txt | ./slim_span.out > tmp.txt; \
	diff tmp.txt out.txt