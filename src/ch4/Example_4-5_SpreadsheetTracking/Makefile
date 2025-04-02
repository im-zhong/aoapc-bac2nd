all:  spreadsheet_tracking_1.out

CXXFLAGS = -std=c++11 -Wall -g

 spreadsheet_tracking_1.out:  spreadsheet_tracking_1.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test:  spreadsheet_tracking_1.out
	cat in.txt | ./spreadsheet_tracking_1.out > tmp.txt; \
	diff tmp.txt out.txt