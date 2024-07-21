all: ancient_cipher.out

CXXFLAGS = -std=c++17 -Wall -g

ancient_cipher.out: ancient_cipher.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: ancient_cipher.out
	cat in.txt | ./ancient_cipher.out > tmp.txt; \
	diff tmp.txt out.txt