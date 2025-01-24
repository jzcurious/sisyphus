cmake_minimum_required(VERSION 3.24)
project(sisyphus-lib LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  deltat
  GIT_REPOSITORY https://github.com/jzcurious/deltat.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(deltat)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(sisyphus INTERFACE)

target_include_directories(sisyphus INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(sisyphus INTERFACE
    deltat
)
