cmake_minimum_required(VERSION 3.16)
project(CounterStrike)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
