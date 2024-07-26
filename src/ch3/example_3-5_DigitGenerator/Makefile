all: digit_generator.out

CXXFLAGS = -Wall -g

digit_generator.out: digit_generator.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: all
	cat in.txt | ./digit_generator.out > tmp.txt; \
	diff tmp.txt out.txt; \
