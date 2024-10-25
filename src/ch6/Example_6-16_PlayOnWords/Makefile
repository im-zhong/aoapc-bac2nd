all: play_on_words.out

CXXFLAGS = -std=c++11 -Wall -g

play_on_words.out: play_on_words.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: play_on_words.out
	cat in.txt | ./play_on_words.out > tmp.txt; \
	diff tmp.txt out.txt