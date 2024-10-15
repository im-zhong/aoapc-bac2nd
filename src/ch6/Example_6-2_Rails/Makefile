all: rails_2.out

CXXFLAGS = -std=c++11 -Wall -g

rails_2.out: rails_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: rails_2.out
	cat in.txt | ./rails_2.out > tmp.txt; \
	diff tmp.txt out.txt