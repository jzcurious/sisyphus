cmake_minimum_required(VERSION 3.24)
project(sisyphus-lib LANGUAGES CXX)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(sisyphus INTERFACE)

target_include_directories(sisyphus INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
