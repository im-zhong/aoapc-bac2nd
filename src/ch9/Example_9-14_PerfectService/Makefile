all: perfect_service.out

CXXFLAGS = -std=c++11 -Wall -g

perfect_service.out: perfect_service.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: perfect_service.out
	cat in.txt | ./perfect_service.out > tmp.txt; \
	diff tmp.txt out.txt