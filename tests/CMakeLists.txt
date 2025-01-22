cmake_minimum_required(VERSION 3.24)
project(sisyphus-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(sisyphus-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_link_libraries(sisyphus-tests PRIVATE
    GTest::gtest_main
    sisyphus
)

enable_testing()
gtest_discover_tests(sisyphus-tests)
