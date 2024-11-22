all: the_tower_of_babylon.out

CXXFLAGS = -std=c++11 -Wall -g

the_tower_of_babylon.out: the_tower_of_babylon.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: the_tower_of_babylon.out
	cat in.txt | ./the_tower_of_babylon.out > tmp.txt; \
	diff tmp.txt out.txt