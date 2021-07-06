cmake_minimum_required(VERSION 3.16)
project(CounterStrike)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -Werror -pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")

file(GLOB_RECURSE CLIENT_SRCS ./client/src/*.cpp)
file(GLOB_RECURSE COMMON_SRCS ./common/src/*.cpp)
file(GLOB_RECURSE SERVER_SRCS ./server/src/*.cpp)
# file(GLOB_RECURSE TEST_SRCS LIST_DIRECTORIES false *.h *.cpp)

list(FILTER CLIENT_SRCS EXCLUDE REGEX "main.cpp")
list(FILTER COMMON_SRCS EXCLUDE REGEX "main.cpp")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(yaml-cpp REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})
# include_directories(client/include)
include_directories(common/include)
# include_directories(server/include)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

add_library(libclient STATIC ${CLIENT_SRCS})
add_library(libcommon STATIC ${COMMON_SRCS})
add_library(libserver STATIC ${SERVER_SRCS})
# add_library(libtest STATIC ${TEST_SRCS})

target_link_libraries(
    libclient 
    ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2TTF_LIBRARY} yaml-cpp
    )

target_link_libraries(libclient -ldl -lBox2D)
target_include_directories(libclient PUBLIC 
client/include)
target_link_libraries(libserver -ldl -lBox2D)
target_include_directories(libserver PUBLIC 
server/include)

target_link_libraries(
    libcommon 
    ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2TTF_LIBRARY} yaml-cpp
    )

# target_link_libraries(libtest libcommon libclient gtest)

add_executable(CounterStrike_server "server/src/main.cpp")
TARGET_LINK_LIBRARIES(CounterStrike_server libserver libcommon)

add_executable(CounterStrike_run "client/src/main.cpp")
TARGET_LINK_LIBRARIES(CounterStrike_run libclient libcommon)

# add_executable(test "client/src/box2d_sdl_test.cpp")
# TARGET_LINK_LIBRARIES(test libclient libcommon)

# add_executable(CounterStrike_test "test/main.cpp")
# TARGET_LINK_LIBRARIES(CounterStrike_test libtest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

install(TARGETS ${BINARY} libclient libcommon
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "bin"
        INCLUDES DESTINATION "include")
install(DIRECTORY resources DESTINATION ".")
install(DIRECTORY maps DESTINATION ".")
install(DIRECTORY config DESTINATION ".")
install(DIRECTORY movies DESTINATION ".")

