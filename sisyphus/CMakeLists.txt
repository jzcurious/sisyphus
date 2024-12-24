cmake_minimum_required(VERSION 3.24)
project(sisyphus-lib LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  indicators
  GIT_REPOSITORY https://github.com/p-ranav/indicators.git
  GIT_TAG v2.3
)
FetchContent_MakeAvailable(indicators)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(sisyphus STATIC ${SRC})

target_include_directories(sisyphus PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sisyphus/
)

target_link_libraries(sisyphus PRIVATE
    indicators
)
