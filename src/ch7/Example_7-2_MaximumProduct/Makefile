all: maximum_product.out

CXXFLAGS = -std=c++11 -Wall -g

maximum_product.out: maximum_product.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: maximum_product.out
	cat in.txt | ./maximum_product.out > tmp.txt; \
	diff tmp.txt out.txt