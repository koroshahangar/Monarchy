INC = -I include
TEAM_INC = -I teams/sample_team
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 $(INC)
GTEST_DIR = /home/korosh/googletest/googletest
GTEST_FLAGS = -isystem ${GTEST_DIR}/include -pthread $(INC)

TESTMODE = 'TEST'

objects = $(addprefix build/, $(addsuffix .o, $(basename $(notdir $(wildcard include/*.h)))))
tests = $(addsuffix .o, $(basename $(filter-out test/main.cc, $(wildcard test/*.cc))))
teams_objects = $(addsuffix .o, $(basename $(wildcard teams/sample_team/*.cc)))


ifdef TESTMODE
test: format $(objects) $(tests) test/main.cc
	$(CXX) $(GTEST_FLAGS) test/main.cc -lgtest -o bin/test $(objects) $(tests)
	bin/test
format:
	astyle --style=google --suffix=none  **/*.h **/*.cc ./*.cc
endif

build: $(objects) $(teams_objects)
	$(CXX) $(CXXFLAGS) $(TEAM_INC) game_setup.cc -o bin/monarchy $(objects) $(teams_objects)

teams/sample_team/%o: teams/sample_team/%.cc teams/sample_team/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test/%.o: test/%.cc
	$(CXX) $(GTEST_FLAGS) -c -o $@  $< -lgtest

.PHONY : clean
clean :
	$(RM) $(objects)
	$(RM) $(tests)
	$(RM) bin/*
