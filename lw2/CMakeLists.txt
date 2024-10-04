cmake_minimum_required(VERSION 3.28)
project(lw2)

set(CMAKE_CXX_STANDARD 26)

add_executable(lw2 main.cpp
        libs/CodeAnalyzer/CodeAnalyzer.cpp
        libs/CodeAnalyzer/CodeAnalyzer.h
        libs/Stack/Stack.cpp
        libs/Stack/Stack.h)
