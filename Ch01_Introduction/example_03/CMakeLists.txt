cmake_minimum_required(VERSION 3.0)
project(example03)

set(Var 2.0)
set(var 55)
set(s1 "Hello world")

message("====================================================")

message("var: " ${var})
message("Var: " ${Var})
message("s1: " ${s1})

set(var 88)
message("Change var: " ${var})

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})

message("====================================================")
