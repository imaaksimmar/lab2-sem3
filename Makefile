.PHONY: all test test-asan benchmark clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
GTEST = -isystem googletest/googletest/include -I googletest/googletest -pthread googletest/googletest/src/gtest-all.cc
TESTS = tests/run_tests.cpp $(wildcard tests/tests_*.cpp)

all: test benchmark

test: $(TESTS)
	$(CXX) $(CXXFLAGS) $(GTEST) $^ -o run_tests
	./run_tests

test-asan: $(TESTS)
	clang++ $(CXXFLAGS) -fsanitize=address,undefined -g -O1 -fno-omit-frame-pointer $(GTEST) $^ -o run_tests_asan
	./run_tests_asan

benchmark: tests/benchmark.cpp
	$(CXX) $(CXXFLAGS) -O2 $< -o run_benchmark
	./run_benchmark

clean:
	rm -f run_tests run_tests_asan run_benchmark results.csv