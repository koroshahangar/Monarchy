INC = -I include
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 $(INC)
GTEST_DIR = /home/korosh/googletest/googletest
GTEST_FLAGS = -isystem ${GTEST_DIR}/include -pthread $(INC)


objects = $(addprefix build/, $(addsuffix .o, $(basename $(notdir $(wildcard src/*.h)))))
tests = $(addsuffix .o, $(basename $(filter-out test/main.cc, $(wildcard test/*.cc))))

test: $(objects) $(tests) test/main.cc	
	$(CXX) $(GTEST_FLAGS) test/main.cc -lgtest -o bin/test $(objects) $(tests)
	bin/test

build/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test/%.o: test/%.cc
	$(CXX) $(GTEST_FLAGS) -c -o $@  $< -lgtest 

.PHONY : clean
clean :
	$(RM) $(objects)
	$(RM) $(tests)
	$(RM) bin/*
