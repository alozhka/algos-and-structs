cmake_minimum_required(VERSION 3.28.1)
project(lw5)

set(CMAKE_CXX_STANDARD 26)

add_executable(lw5 main.cpp
        libs/BTree.cpp
        libs/BTree.h)
