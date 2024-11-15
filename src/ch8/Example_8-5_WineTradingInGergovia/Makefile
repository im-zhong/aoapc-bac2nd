all: wine_trading_in_gergovia.out

CXXFLAGS = -std=c++11 -Wall -g

wine_trading_in_gergovia.out: wine_trading_in_gergovia.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: wine_trading_in_gergovia.out
	cat in.txt | ./wine_trading_in_gergovia.out > tmp.txt; \
	diff tmp.txt out.txt