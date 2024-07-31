all:  the_dole_queue.out

CXXFLAGS = -std=c++17 -Wall -g

 the_dole_queue.out:  the_dole_queue.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test:  the_dole_queue.out
	cat in.txt | ./the_dole_queue.out > tmp.txt; \
	diff tmp.txt out.txt