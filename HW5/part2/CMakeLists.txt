cmake_minimum_required(VERSION 3.22)
project(part2)

set(CMAKE_CXX_STANDARD 11)

add_executable(part2 main.cpp List.h)
add_executable(part2_test testCheckWinSolved1.cpp)
add_executable(part2_test2 Part2Examples.cpp)
add_executable(lev_test lev_test.cpp)
add_executable(akiva_test akivaTests.cpp)
add_executable(RushHourTests RushHourTests.cpp)


