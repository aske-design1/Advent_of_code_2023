# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Advent_of_code VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "day13_cpp/*.cpp")

# Add an executable target called "your_executable_name" from the source file "main.cpp"
add_executable(day13 ${SOURCES})