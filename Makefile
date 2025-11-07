CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -g

SRC = $(wildcard *.cpp)
SRC := $(filter-out generate_test_preferences.cpp, $(SRC))

TEST_SRC = generate_test_preferences.cpp

BIN = app
TEST_BIN = test_data

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_BIN)

clean:
	rm -f $(BIN) $(TEST_BIN)