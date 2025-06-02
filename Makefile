GTEST_INC_DIR ?= /usr/local/include
GTEST_LIB_DIR ?= /usr/local/lib
GMOCK_INCLUDE_DIR ?= /usr/local/include
GMOCK_LIB_DIR ?= /usr/local/lib 

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude -I$(GTEST_INC_DIR) -I$(GMOCK_INCLUDE_DIR) 

GTEST_LIBS = -L$(GTEST_LIB_DIR) -lgtest_main -lgtest
GMOCK_LIBS = -L$(GMOCK_LIB_DIR) -lgmock_main -lgmock

LDFLAGS = -L$(GTEST_LIB_DIR) -lgtest_main -lgtest -pthread


SRC_DIR = src
INCLUDE_DIR = include
TEST_SRC_DIR = test

OBJ_DIR = build
TEST_OBJ_DIR = build/test

TARGET = game
TEST_TARGET = run_tests

SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
TEST_SRC_FILES = $(shell find $(TEST_SRC_DIR) -type f -name '*.cpp')

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_OBJ_FILES = $(patsubst $(TEST_SRC_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

GAME_OBJS_FOR_TEST_RUNNER = $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))

$(TEST_TARGET): $(GAME_OBJS_FOR_TEST_RUNNER) $(TEST_OBJ_FILES)
	$(CXX) $(GAME_OBJS_FOR_TEST_RUNNER) $(TEST_OBJ_FILES) $(GTEST_LIBS) $(GMOCK_LIBS) -pthread -o $@ 

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $< #

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(TARGET) $(TEST_TARGET) 

.PHONY: all clean test $(TEST_TARGET)