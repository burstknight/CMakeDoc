cmake_minimum_required(VERSION 3.0)
project(example_05)

if(WIN32)
	message(STATUS "OS is windows.")
else()
	message(STATUS "OS is not windows.")
endif()
