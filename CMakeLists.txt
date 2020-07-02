cmake_minimum_required(VERSION 3.10)
project(DeckAnalyzer)

# C++11 is required for Catch2 Unit Tests
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# The main DeckAnalyzer executable
add_executable(DeckAnalyzer src/main.cpp)

# Catch2 Unit Tests
find_package(Catch2 REQUIRED)
add_executable(Tests
  tests/AnalyzerTests.cpp
  src/Analyzer.cpp
)
target_include_directories(Tests PUBLIC
  inc
)
target_link_libraries(Tests Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(Tests)
