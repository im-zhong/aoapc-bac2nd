all: send_a_table.out

CXXFLAGS = -std=c++11 -Wall -g

send_a_table.out: send_a_table.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: send_a_table.out
	cat in.txt | ./send_a_table.out > tmp.txt; \
	diff tmp.txt out.txt