cmake_minimum_required(VERSION 3.1.0)
project(bignumCalculator)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 17)

add_executable(bnCalc ${SOURCES})
