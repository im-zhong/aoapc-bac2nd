all: amphiphilic_carbon_molecules.out

CXXFLAGS = -std=c++11 -Wall -g

amphiphilic_carbon_molecules.out: amphiphilic_carbon_molecules.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: amphiphilic_carbon_molecules.out
	cat in.txt | ./amphiphilic_carbon_molecules.out > tmp.txt; \
	diff tmp.txt out.txt