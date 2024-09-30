cmake_minimum_required(VERSION 3.28)
project(lw3)

set(CMAKE_CXX_STANDARD 26)

add_executable(lw3 main.cpp
        libs/TreeViewer.cpp
        libs/TreeViewer.h)
