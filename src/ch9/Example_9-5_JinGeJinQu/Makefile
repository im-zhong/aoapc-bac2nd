all: jin_ge_jin_qu_2.out

CXXFLAGS = -std=c++11 -Wall -g

jin_ge_jin_qu_2.out: jin_ge_jin_qu_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: jin_ge_jin_qu_2.out
	cat in.txt | ./jin_ge_jin_qu_2.out > tmp.txt; \
	diff tmp.txt out.txt