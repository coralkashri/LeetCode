cmake_minimum_required(VERSION 3.28.1)

project(LeetCode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++23")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

#generate_all_exercises_includes_file()

SET(EXERCISES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/exercises)
set(ALL_EXERCISES_FILE ${EXERCISES_DIR}/all.hpp)

add_custom_command(
        OUTPUT ${ALL_EXERCISES_FILE}
        COMMAND ${CMAKE_COMMAND} -E remove ${ALL_EXERCISES_FILE}
        COMMAND echo "" > ${ALL_EXERCISES_FILE}
        COMMENT "Removing ${ALL_EXERCISES_FILE}"
        VERBATIM
)

add_custom_target(
        create_file_target
        ALL
        COMMAND echo "Command: Creating ${ALL_EXERCISES_FILE}"
        COMMAND ${CMAKE_COMMAND} -P ../src/exercises/generate_all_includes_file.cmake
        COMMENT "Creating ${ALL_EXERCISES_FILE}"
        DEPENDS ${ALL_EXERCISES_FILE}
        VERBATIM
)

file(GLOB_RECURSE SOURCE_FILES src/*)

add_executable(AdventOfCode2021 ${SOURCE_FILES} ${ALL_EXERCISES_FILE})

add_dependencies(AdventOfCode2021 create_file_target)