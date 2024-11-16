all: sliding_window_minimum_mono_queue.out

CXXFLAGS = -std=c++11 -Wall -g

sliding_window_minimum_mono_queue.out: sliding_window_minimum_mono_queue.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: sliding_window_minimum_mono_queue.out
	cat in.txt | ./sliding_window_minimum_mono_queue.out > tmp.txt; \
	diff tmp.txt out.txt