cmake_minimum_required(VERSION 3.18)
project(AdventOfCode2021)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++23 -static-libstdc++")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB_RECURSE SOURCE_FILES src/* src/exercises/*)

add_executable(AdventOfCode2021 ${SOURCE_FILES} src/main.cpp)