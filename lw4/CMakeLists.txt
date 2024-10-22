cmake_minimum_required(VERSION 3.28)
project(lw4)

set(CMAKE_CXX_STANDARD 26)

add_executable(lw4 main.cpp
        libs/Graph.cpp
        libs/Graph.h)
