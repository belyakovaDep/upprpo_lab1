cmake_minimum_required(VERSION 3.14)


# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/src)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
  hello_test2
  tests.cpp ${PROJECT_SOURCE_DIR}/src/BitArray.cpp
)
target_link_libraries(
  hello_test2
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test2)
