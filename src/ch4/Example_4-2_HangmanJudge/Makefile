all: hangman_judge.out

CXXFLAGS = -std=c++17 -Wall -g

hangman_judge.out: hangman_judge.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: hangman_judge.out
	cat in.txt | ./hangman_judge.out > tmp.txt; \
	diff tmp.txt out.txt