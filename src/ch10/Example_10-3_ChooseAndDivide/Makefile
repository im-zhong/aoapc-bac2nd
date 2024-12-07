all: choose_and_divide.out

CXXFLAGS = -std=c++11 -Wall

choose_and_divide.out: choose_and_divide.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: choose_and_divide.out
	cat in.txt | ./choose_and_divide.out > tmp.txt; \
	diff tmp.txt out.txt