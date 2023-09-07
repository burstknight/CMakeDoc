cmake_minimum_required(VERSION 3.5)

project(example_06)

set(var 3)
if(${var} GREATER 4)
	message("var > 4")
elseif(${var} GREATER 3 OR ${var} EQUAL 3)
	message("var > 3")
else()
	message("var < 3")
endif(${var} GREATER 4)

