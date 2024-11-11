all: huffman.out

CXXFLAGS = -std=c++11 -Wall -g

huffman.out: huffman.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: huffman.out
	cat in.txt | ./huffman.out > tmp.txt; \
	diff tmp.txt out.txt