cmake_minimum_required(VERSION 3.16)
project(CounterStrike)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src)

add_compile_options(-w -lSDL2 -lSDL2_image -std=c++11)

add_subdirectory(src)
add_subdirectory(test)
