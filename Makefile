INC = -I include
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 $(INC)
GTEST_DIR = /home/korosh/googletest/googletest
GTEST_FLAGS = -isystem ${GTEST_DIR}/include -pthread $(INC)

TESTMODE = 'TEST'

objects = $(addprefix build/, $(addsuffix .o, $(basename $(notdir $(wildcard include/*.h)))))
tests = $(addsuffix .o, $(basename $(filter-out test/main.cc, $(wildcard test/*.cc))))


ifdef TESTMODE
test: format $(objects) $(tests) test/main.cc
	$(CXX) $(GTEST_FLAGS) test/main.cc -lgtest -o bin/test $(objects) $(tests)
	bin/test
format:
	astyle --style=google --recursive --suffix=none  *.h *.cc
endif

build: $(objects)
	$(CXX) $(INC) config/game_setup.cc -o bin/monarchy $(objects)

build/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test/%.o: test/%.cc
	$(CXX) $(GTEST_FLAGS) -c -o $@  $< -lgtest

.PHONY : clean
clean :
	$(RM) $(objects)
	$(RM) $(tests)
	$(RM) bin/*
