all: team_queue.out team_queue_2.out

CXXFLAGS = -std=c++11 -Wall -g

team_queue.out: team_queue.cpp
	c++ $(CXXFLAGS) -o $@ $^

team_queue_2.out: team_queue_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: team_queue.out team_queue_2.out
	cat in.txt | ./team_queue.out > tmp.txt; \
	diff tmp.txt out.txt \
	&& cat in.txt | ./team_queue_2.out > tmp_2.txt; \
	diff tmp_2.txt out.txt
