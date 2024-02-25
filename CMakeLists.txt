# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Advent_of_code VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "day13_cpp/*.cpp")
file(GLOB SOURCES "day14_cpp/*.cpp")

# Add an executable target called "your_executable_name" from the source file "main.cpp"
add_executable(day13
        Day13_cpp/main13.cpp)
add_executable(day14
        Day14_cpp/main.cpp)

add_executable(day12
        Day12_cpp/main.cpp
        Day12_cpp/functions.cpp)