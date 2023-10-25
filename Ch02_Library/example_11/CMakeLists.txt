cmake_minimum_required(VERSION 3.5)

project(exmaple_11)

find_package(ColorPrint CONFIG REQUIRED)

aux_source_directory(./src Srcs)

add_executable(use_lib ${Srcs})

target_link_libraries(use_lib ColorPrint)
