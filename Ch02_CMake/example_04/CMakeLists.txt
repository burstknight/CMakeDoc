cmake_minimum_required(VERSION 3.5)

project(example02)

include_directories(src)

aux_source_directory(src SRCS)

add_executable(myPow ${SRCS})
