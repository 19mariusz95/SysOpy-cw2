cmake_minimum_required(VERSION 3.3)
project(zad3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES main.c)
add_executable(zad3 ${SOURCE_FILES})