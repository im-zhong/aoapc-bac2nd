all: unix_ls.out

CXXFLAGS = -std=c++11 -Wall -g

unix_ls.out: unix_ls.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: unix_ls.out
	cat in.txt | ./unix_ls.out > tmp.txt \
	diff tmp.txt out.txt