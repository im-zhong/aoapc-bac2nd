all: ananagrams.out ananagrams_2.out

CXXFLAGS = -std=c++11 -Wall -g

ananagrams.out: ananagrams.cpp
	c++ $(CXXFLAGS) -o $@ $^

ananagrams_2.out: ananagrams_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ananagrams.out ananagrams_2.out
	cat in.txt | ./ananagrams.out > tmp.txt; \
	diff tmp.txt out.txt \
	&& cat in.txt | ./ananagrams_2.out > tmp_2.txt; \
	diff tmp_2.txt out.txt
