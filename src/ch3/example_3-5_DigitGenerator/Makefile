all: digit_generator.out digit_generator_2.out

CXXFLAGS = -Wall -g

digit_generator.out: digit_generator.cpp
	c++ $(CXXFLAGS) -o $@ $^

digit_generator_2.out: digit_generator_2.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: all
	cat in.txt | ./digit_generator.out > tmp.txt; \
	diff tmp.txt out.txt; \
	cat in.txt | ./digit_generator_2.out > tmp.txt; \
	diff tmp.txt out.txt