all: peoridic_strings.out

CXXFLAGS = -Wall -g

peoridic_strings.out: peoridic_strings.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: peoridic_strings.out
	cat in.txt | ./peoridic_strings.out > tmp.txt; \
	diff tmp.txt out.txt