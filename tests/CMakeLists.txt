cmake_minimum_required(VERSION 3.24)
project(udl-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(udl-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_link_libraries(udl-tests PRIVATE
    GTest::gtest_main
    udl
)

enable_testing()
gtest_discover_tests(udl-tests)
