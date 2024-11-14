all: building_for_un.out

CXXFLAGS = -std=c++11 -Wall -g

building_for_un.out: building_for_un.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: building_for_un.out
	cat in.txt | ./building_for_un.out > tmp.txt; \
	diff tmp.txt out.txt