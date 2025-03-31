all: buy_or_build.out

CXXFLAGS = -std=c++11 -Wall -g

buy_or_build.out: buy_or_build.cpp
	c++ $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM tmp.txt

test: buy_or_build.out
	cat in.txt | ./buy_or_build.out > tmp.txt; \
	diff tmp.txt out.txt

profile: buy_or_build.cpp
	clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping buy_or_build.cpp -o buy_or_build.out && \
	LLVM_PROFILE_FILE="coverage.profraw" ./buy_or_build.out < in.txt && \
	llvm-profdata merge -sparse coverage.profraw -o coverage.profdata && \
	llvm-cov show ./buy_or_build.out -instr-profile=coverage.profdata 
	

