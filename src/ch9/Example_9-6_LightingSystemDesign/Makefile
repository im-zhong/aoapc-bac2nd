all: lighting_system_design.out

CXXFLAGS = -std=c++11 -Wall -g

lighting_system_design.out: lighting_system_design.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: lighting_system_design.out
	cat in.txt | ./lighting_system_design.out > tmp.txt; \
	diff tmp.txt out.txt