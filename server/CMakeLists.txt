cmake_minimum_required(VERSION 3.16)

project(counter_strike)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FetchContent)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

file(GLOB src "src/*.cpp")

add_library(counter-strike-src ${src})

include_directories(${PROJECT_BINARY_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(server src/main.cpp)

enable_testing()

add_executable(
  tests
  test/map.cpp
  test/configuration.cpp
  test/player.cpp
)

target_link_libraries(
  tests
  gtest_main
  counter-strike-src
  yaml-cpp
)

include(GoogleTest)
gtest_discover_tests(tests)

target_link_libraries(server counter-strike-src yaml-cpp)
