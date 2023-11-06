cmake_minimum_required(VERSION 3.5)

project(example_11)

find_package(myMathLib 1.0 REQUIRED)
include_directories(${myMathLib_INCLUDE_DIRS})

aux_source_directory(./src Source_Files)
add_executable(exe ${Source_Files})
target_link_libraries(exe myMathLib)

