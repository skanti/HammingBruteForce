cmake_minimum_required(VERSION 3.0)
project(HamingBruteForce CXX)

# -> required packages
find_package(Eigen3 3.3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
# <-

set(CMAKE_CXX_COMPILER "c++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-result -O3 -msse4 -Wall -std=c++14 -DSIZE_BITS_HAMING=64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")


set(SOURCE_FILES_CPP
        src/HammingBruteForce.cpp)

set(SOURCE_FILES_H
        src/HammingBruteForce.h
        src/Types.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_library(HammingBruteForce ${SOURCE_FILES_CPP} ${SOURCE_FILES_H})

add_executable(HammingBruteForceExample example/main.cpp example/Timer.h)
target_link_libraries(HammingBruteForceExample HammingBruteForce)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.h
        PRE_BUILD
        COMMAND m4 -DSIZE_BITS_HAMING=64 -DN_THREADS=4 ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.m4 > ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.h
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.m4
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Creating m4 files.")


set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.h PROPERTIES GENERATED true)
