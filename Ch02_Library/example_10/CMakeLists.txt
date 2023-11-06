cmake_minimum_required(VERSION 3.5)

project(example_10)

# 新增一個選項，可以用來控制要不要做單元測試
option(Enable_Unit_Test "Do you want to do unit test?" ON)

# 新增一個選項，可以決定是要使用標頭檔`assert.h`提供的巨集`assert()`來做單元測試，
# 又或是單純使用執行檔`myExe`和`CTest`來做單元測試
option(Enable_Assert_Test "Do you want to use the macro assert() to do unit test" OFF)

# 設定標頭檔所在的位置
include_directories(./includes)

# 宣告變數`Lib_Name`為`myMathLib`，作為函數庫的名稱
set(Lib_Name myMathLib)

set(Lib_Version_Major 1)
set(Lib_Version_Minor 0)
set(Lib_Version "${Lib_Version_Major}.${Lib_Version_Minor}")

# 進入子目錄`src`中處理該子目錄的`CMakeLists.txt`
add_subdirectory(./src)

aux_source_directory(./src Source_Files)

add_executable(myExe ${Source_Files})

# 把函數庫`myMathLib`連結進可執行檔中
target_link_libraries(myExe ${Lib_Name})

# 透過`install()`這個指令來安裝可執行檔`myExe`
install(TARGETS myExe DESTINATION lib/${Lib_Name} EXPORT ${Lib_Name}-targets)

# 透過`install(EXPORT ...)`在安裝的過程中產生特殊的目標檔
install(EXPORT ${Lib_Name}-targets DESTINATION lib/myMathLib)

# 新增自訂的指令，讓makefile也能使用`uninstall`來解除安裝
add_custom_target("uninstall" COMMENT "Uninstall installed files.")
add_custom_command(
	TARGET "uninstall"
	POST_BUILD
	COMMENT "Uninstall files from this computer."
	COMMAND rm -rfv ${CMAKE_INSTALL_PREFIX}/include/${Lib_Name}
	COMMAND rm -rfv ${CMAKE_INSTALL_PREFIX}/lib/${Lib_Name}
	)

if(${Enable_Unit_Test})
	enable_testing()
	add_subdirectory(./test)
endif()

