cmake_minimum_required(VERSION 3.5)

project(example_10)

set(CMAKE_C_STANDARD 99)

# 用來處理建置的設定標頭檔
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
	)

# 設定安裝路徑為`/tmp`
#set(CMAKE_INSTALL_PREFIX /tmp)

set(Lib_Name "ColorPrint")

# 新增一個建置的設定，可選擇是否要使用`ColorPrint`這個函式庫
option(USE_COLOR_PRINT "Use color print lib" ON)

if(USE_COLOR_PRINT)
	include_directories("${PROJECT_SOURCE_DIR}/ColorPrint")
	add_subdirectory(ColorPrint)
	set(Extra_Libs ${Extra_Libs} ColorPrint)
endif(USE_COLOR_PRINT)

aux_source_directory(. Src)
add_executable(testColorPrint ${Src})
target_link_libraries(testColorPrint ${Extra_Libs})


install(TARGETS testColorPrint DESTINATION bin)
install(FILES "${PROJECT_SOURCE_DIR}/config.h" DESTINATION include/ColorPrint)
install(FILES cmake/ColorPrintConfig.cmake DESTINATION lib/cmake/${Lib_Name})


# 新增一個指令，可以透過 `make uninstall` 解除安裝
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
	TARGET "uninstall"
	POST_BUILD
	COMMENT "Uninstall files with install_mainifest.txt"
	COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in install_manifest.txt to be uninstalled!
	)
