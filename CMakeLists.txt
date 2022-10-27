cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

#set(CMAKE_BUILD_TYPE Debug)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(HelloWorld)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(HelloWorld ${project_SRCS})
target_link_libraries(HelloWorld ${SDL2_LIBRARIES})
