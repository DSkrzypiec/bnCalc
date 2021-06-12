cmake_minimum_required(VERSION 3.1.0)
project(bnCalc)

file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
