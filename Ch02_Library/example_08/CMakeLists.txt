cmake_minimum_required(VERSION 3.5)

project(example_08)

set(CMAKE_C_STANDARD 99)

add_subdirectory(ColorPrint)

aux_source_directory(. Src)
add_executable(myPrint ${Src})
target_link_libraries(myPrint ColorPrint)
