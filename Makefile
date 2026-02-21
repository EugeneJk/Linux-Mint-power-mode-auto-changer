VERSION=2.0.0
PACKAGE=power-mode-auto-changer
BUILD_DIR=build

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2 -Isrc
BUILD_DIR = build
SRC_DIR = src

SERVICE_TARGET = power-mode-auto-switcher-service
CLI_TARGET = power-mode-auto-switcher-cli
TEST_TARGET = test

COMMON_SOURCES := $(shell find $(SRC_DIR) -mindepth 2 -name "*.cpp")
SERVICE_SOURCE := $(SRC_DIR)/service.cpp
CLI_SOURCE := $(SRC_DIR)/cli.cpp
TEST_SOURCE := $(SRC_DIR)/test.cpp

all: $(SERVICE_TARGET) $(CLI_TARGET) $(TEST_TARGET)

$(SERVICE_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SERVICE_SOURCE) $(COMMON_SOURCES) -o $(BUILD_DIR)/$(SERVICE_TARGET)

$(CLI_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CLI_SOURCE) $(COMMON_SOURCES) -o $(BUILD_DIR)/$(CLI_TARGET)

$(TEST_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(COMMON_SOURCES) -o $(BUILD_DIR)/$(TEST_TARGET)


clean:
	rm -rf $(BUILD_DIR)
