cmake_minimum_required(VERSION 3.28)
project(lw1)

set(CMAKE_CXX_STANDARD 26)

set(BOOST_ROOT /usr/include/boost)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(lw1 main.cpp
        libs/files-handler.h
        libs/files-handler.cpp)
