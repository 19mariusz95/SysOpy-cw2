cmake_minimum_required(VERSION 3.3)
project(zad1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES main.c main2.c)
add_executable(zad1a main.c)
add_executable(zad1b main2.c)