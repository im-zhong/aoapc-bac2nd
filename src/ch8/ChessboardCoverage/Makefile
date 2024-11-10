all: chessboard_coverage.out

CXXFLAGS = -std=c++11 -Wall -g

chessboard_coverage.out: chessboard_coverage.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: chessboard_coverage.out
	cat in.txt | ./chessboard_coverage.out > tmp.txt; \
	diff tmp.txt out.txt