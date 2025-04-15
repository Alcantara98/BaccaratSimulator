cmake_minimum_required(VERSION 3.10)
project(baccarat)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create compile_commands.json for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to enable high optimization
option(RELEASE "Release Build, enable optimization" OFF)

message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

if(RELEASE)
    message(STATUS "Building with high optimization")
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -flto")
endif()

# Create the executable
add_executable(baccarat ${SOURCES})
