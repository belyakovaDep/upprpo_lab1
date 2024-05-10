cmake_minimum_required(VERSION 3.14)
set(CXX_STANDARD 17)
project(my-project)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

option(MATCH_TESTS "build tests (or no)" ON)

if (MATCH_TESTS)
        add_library(example_google_tests ${all_SRCS})
        enable_testing()
        add_subdirectory(tests)
endif()


add_executable(app ${all_SRCS})
