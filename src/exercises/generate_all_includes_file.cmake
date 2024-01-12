cmake_minimum_required(VERSION 3.28.1)

SET(EXERCISES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/exercises)
set(ALL_EXERCISES_FILE ${EXERCISES_DIR}/all.hpp)

file(GLOB_RECURSE EXERCISES ../src/exercises/*)
file(WRITE ${ALL_EXERCISES_FILE} "#pragma once\n\n")
file(APPEND ${ALL_EXERCISES_FILE} "/*********************************************\n * This file was generated be CMakeLists.txt\n * cmake is cool, use it\n *********************************************/\n\n")

set(IGNORED_FILES generate_all_includes_file.cmake all.hpp)

foreach (FILE IN LISTS EXERCISES)
    file(RELATIVE_PATH REL_FILE_PATH ${EXERCISES_DIR} ${FILE})

    if (${REL_FILE_PATH} IN_LIST IGNORED_FILES)
        continue()
    endif ()

    message(STATUS "Adding ${REL_FILE_PATH} to src/exercises/all.hpp includes.")
    file(APPEND ${ALL_EXERCISES_FILE} "#include \"${REL_FILE_PATH}\"\n")
endforeach ()