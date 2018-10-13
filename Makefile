INC = -I include
TEAMS_DIR := $(wildcard teams/*)
TEAMS_INC := $(foreach dir,$(TEAMS_DIR), -I $(dir))
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 $(INC)
GTEST_DIR = /home/korosh/googletest/googletest
GTEST_FLAGS = -isystem ${GTEST_DIR}/include -pthread $(INC)

server_objects = $(addprefix build/, $(addsuffix .o, $(basename $(notdir $(wildcard include/*.h)))))
tests = $(addsuffix .o, $(basename $(filter-out test/main.cc, $(wildcard test/*.cc))))
teams_objects = $(addsuffix .o, $(basename $(wildcard teams/*/*.cc)))

monarchy: server teams
	$(CXX) $(CXXFLAGS) $(TEAMS_INC) game_setup.cc -o bin/monarchy $(server_objects) $(teams_objects)

server: $(server_objects)

teams: $(teams_objects)

build/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
tests: format $(server_objects) $(tests) test/main.cc
	$(CXX) $(GTEST_FLAGS) test/main.cc -lgtest -o bin/test $(server_objects) $(tests)
	bin/test
format:
	astyle --style=google --suffix=none  **/*.h **/*.cc ./*.cc

test/%.o: test/%.cc
	$(CXX) $(GTEST_FLAGS) -c -o $@  $< -lgtest

.PHONY : clean
clean : clean-teams clean-server clean-tests
	$(RM) bin/*
clean-teams:
	$(RM) $(teams_objects)
clean-server:
	$(RM) $(server_objects)
clean-tests:
	$(RM) $(tests)
