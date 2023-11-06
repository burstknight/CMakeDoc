# 在當前的資料夾中找出所有的`.c`檔
aux_source_directory(. Lib_Source_FIles)

# 把所有原始碼檔案編譯成static library，而且該函式庫的名稱為`myMathLib`
add_library(${Lib_Name} ${Lib_Source_FIles})

# 使用`install()`這個指令安裝函式庫`myMathLib`
install(TARGETS ${Lib_Name} DESTINATION lib/${Lib_Name}
	EXPORT ${Lib_Name}-targets)

# 使用樣板產生標頭檔`verison.h`，用來記錄函式庫的版本號，
# 並且使用`install()`來安裝標頭檔
configure_file(${CMAKE_SOURCE_DIR}/includes/version.h.in
	${CMAKE_SOURCE_DIR}/includes/version.h @ONLY)
install(FILES ${CMAKE_SOURCE_DIR}/includes/version.h
	${CMAKE_SOURCE_DIR}/includes/myMathLib.h
	DESTINATION include/${Lib_Name})

# 使用樣板產生`myMathLibConfig.cmake`，讓其他專案可以透過這個檔案
# 取得該函式庫的標頭檔路徑和函式庫檔的位置
configure_file(
	${CMAKE_SOURCE_DIR}/cmake/${Lib_Name}Config.cmake.in
	${CMAKE_BINARY_DIR}/cmake/${Lib_Name}Config.cmake @ONLY)

# 使用樣板產生`myMathLibConfig-version.cmake`，讓其他專案可以透過這個檔案
# 判斷版本是否可用
configure_file(
	${CMAKE_SOURCE_DIR}/cmake/${Lib_Name}Config-version.cmake.in
	${CMAKE_BINARY_DIR}/cmake/${Lib_Name}Config-version.cmake @ONLY)

# 使用`install()`安裝`myMathLibConfig.cmake`和`myMathLibConfig-version.cmake`
install(FILES ${CMAKE_BINARY_DIR}/cmake/${Lib_Name}Config.cmake
	${CMAKE_BINARY_DIR}/cmake/${Lib_Name}Config-version.cmake
	DESTINATION lib/${Lib_Name})

