cmake_minimum_required(VERSION 3.12)
project(BitPacker)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
# include_directories(tests)
add_executable(run_test src/main.cpp src/BitPacker.cpp)
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# get all tests from tests folder
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES} src/BitPacker.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(tests)
