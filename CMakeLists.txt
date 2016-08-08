cmake_minimum_required(VERSION 3.0)
project(HamingBruteForce CXX)

set(CMAKE_CXX_COMPILER "/usr/local/bin/icpc")
SET(OPTIMIZATION_FLAGS "-O3 -qopenmp -fomit-frame-pointer -march=native")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wall -std=c++14")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(SOURCE_FILES_CPP
        src/HamingBruteForce.cpp)

set(SOURCE_FILES_H
        src/HamingBruteForce.h
        src/AlignedAllocator.h)

add_library(HamingBruteForce ${SOURCE_FILES_CPP} ${SOURCE_FILES_H})

include_directories(./src)
add_executable(HamingBruteForceExample example/main.cpp example/Timer.h)
target_link_libraries(HamingBruteForceExample HamingBruteForce)