cmake_minimum_required(VERSION 3.0)
project(HamingBruteForce CXX)

set(CMAKE_CXX_COMPILER "/usr/local/bin/icpc")
set(OPTIMIZATION_FLAGS "-O3 -qopenmp -fomit-frame-pointer -march=native")
set(USER_DEFINES "-DSIZE_BITS_HAMING=64 -DN_THREADS=4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wall -std=c++14 ${USER_DEFINES}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")


set(SOURCE_FILES_CPP
        ./src/HamingBruteForce.cpp)

set(SOURCE_FILES_H
        src/MathKernels.h
        src/HamingBruteForce.h
        src/AlignedAllocator.h
        src/Types.h)

include_directories(./src)
add_library(HamingBruteForce ${SOURCE_FILES_CPP} ${SOURCE_FILES_H})

add_executable(HamingBruteForceExample example/main.cpp example/Timer.h)
target_link_libraries(HamingBruteForceExample HamingBruteForce)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.h
        PRE_BUILD
        COMMAND m4 -DSIZE_BITS_HAMING=64 -DN_THREADS=4 ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.m4 > $@
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/MathKernels.m4
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT ${USER_DEFINES})

set_source_files_properties(src/MathKernels.h PROPERTIES EXTERNAL_OBJECT true GENERATED true)