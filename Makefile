CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := lab3_segmented_deque
TEST_TARGET := lab3_tests
SOURCES := main.cpp
TEST_SOURCES := test_runner.cpp

.PHONY: all run tests smoke clean

all: $(TARGET)

$(TARGET): $(SOURCES) *.h *.tpp *.cpp
	@echo "Building in: $(CURDIR)"
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

$(TEST_TARGET): $(TEST_SOURCES) Tests.h tests.tpp *.h *.tpp *.cpp
	@echo "Building tests in: $(CURDIR)"
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

tests: $(TEST_TARGET)
	./$(TEST_TARGET)

smoke: $(TARGET)
	printf '0\n1\n1\n0\n' | ./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
