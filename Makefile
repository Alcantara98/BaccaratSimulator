# Simple CMake shortcuts
BUILD_DIR := build
TARGET := baccarat

.PHONY: configure build run clean reconfigure release

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/$(TARGET)

release:
	cmake -S . -B $(BUILD_DIR) -DRELEASE=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build $(BUILD_DIR)

clean:
	cmake --build $(BUILD_DIR) --target clean

rebuild: clean build