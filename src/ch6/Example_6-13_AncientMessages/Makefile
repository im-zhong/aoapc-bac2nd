all: ancient_messages.out

CXXFLAGS = -std=c++11 -Wall -g

ancient_messages.out: ancient_messages.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ancient_messages.out
	cat in.txt | ./ancient_messages.out > tmp.txt; \
	diff tmp.txt out.txt