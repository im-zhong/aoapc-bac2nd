all: team_queue.out

CXXFLAGS = -std=c++11 -Wall -g

team_queue.out: team_queue.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: team_queue.out
	cat in.txt | ./team_queue.out > tmp.txt; \
	diff tmp.txt out.txt