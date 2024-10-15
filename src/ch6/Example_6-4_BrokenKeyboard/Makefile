all: broken_keyboard.out

CXXFLAGS = -std=c++11 -Wall -g

broken_keyboard.out: broken_keyboard.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: broken_keyboard.out
	cat in.txt | ./broken_keyboard.out > tmp.txt; \
	diff tmp.txt out.txt