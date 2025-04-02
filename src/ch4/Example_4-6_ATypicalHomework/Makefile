all:  a_typical_homework.out

CXXFLAGS = -std=c++11 -Wall -g

 a_typical_homework.out:  a_typical_homework.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test:  a_typical_homework.out
	cat in.txt | ./a_typical_homework.out > tmp.txt; \
	diff tmp.txt out.txt 