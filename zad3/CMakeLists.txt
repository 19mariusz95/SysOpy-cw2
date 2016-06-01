cmake_minimum_required(VERSION 3.3)
project(zad3 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c)
add_executable(zad3 ${SOURCE_FILES})