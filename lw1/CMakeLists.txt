cmake_minimum_required(VERSION 3.28)
project(lw1)

set(CMAKE_CXX_STANDARD 26)

add_executable(lw1 main.cpp
        libs/files-hanlder.h
        libs/files-hanlder.cpp)
