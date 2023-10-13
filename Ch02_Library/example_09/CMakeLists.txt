cmake_minimum_required(VERSION 3.5)

project(example_09)

set(CMAKE_C_STANDARD 99)

# 用來處理建置的設定標頭檔
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
	)


# 新增一個建置的設定，可選擇是否要使用`ColorPrint`這個函式庫
option(USE_COLOR_PRINT "Use color print lib" ON)

if(USE_COLOR_PRINT)
	include_directories("${PROJECT_SOURCE_DIR}/ColorPrint")
	add_subdirectory(ColorPrint)
	set(Extra_Libs ${Extra_Libs} ColorPrint)
endif(USE_COLOR_PRINT)

aux_source_directory(. Src)
add_executable(myPrint ${Src})
target_link_libraries(myPrint ${Extra_Libs})
