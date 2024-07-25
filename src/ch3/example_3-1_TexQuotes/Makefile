all: tex_quotes.out

CXXFLAGS = -Wall -g

tex_quotes.out: tex_quotes.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: tex_quotes.out
	cat in.txt | ./tex_quotes.out > tmp.txt; \
	diff tmp.txt out.txt