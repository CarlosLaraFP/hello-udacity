cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

project(hello_udacity)

add_executable(hello hello.cpp date.cpp)