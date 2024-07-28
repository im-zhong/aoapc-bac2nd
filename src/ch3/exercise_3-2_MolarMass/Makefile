all: molar_mass.out

CXXFLAGS = -Wall -g

molar_mass.out: molar_mass.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: molar_mass.out
	cat in.txt | ./molar_mass.out > tmp.txt; \
	diff tmp.txt out.txt