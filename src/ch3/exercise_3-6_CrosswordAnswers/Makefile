all: crossword_answers.out

CXXFLAGS = -Wall -g

crossword_answers.out: crossword_answers.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: crossword_answers.out
	cat in.txt | ./crossword_answers.out > tmp.txt; \
	diff tmp.txt out.txt