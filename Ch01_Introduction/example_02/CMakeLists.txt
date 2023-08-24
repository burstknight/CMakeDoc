cmake_minimum_required(VERSION 3.0)

project(example02)

include_directories(src)

add_executable(myPow src/main.c src/calcPow.c)
