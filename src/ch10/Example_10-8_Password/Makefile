all: password.out

CXXFLAGS = -std=c++11 -Wall -g

password.out: password.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: password.out
	cat in.txt | ./password.out > tmp.txt; \
	diff tmp.txt out.txt