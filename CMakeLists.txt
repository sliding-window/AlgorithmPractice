cmake_minimum_required (VERSION 3.5)

project(AlgorithmPractice)

set(CMAKE_CXX_FLAGS "-std=c++11 -o3 -Wall -g")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(GTest REQUIRED)
message("-- GTest directory: " ${GTEST_INCLUDE_DIRS})
message("-- GTest library: " ${GTEST_BOTH_LIBRARIES})
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(src)
