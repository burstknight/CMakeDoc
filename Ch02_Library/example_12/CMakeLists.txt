cmake_minimum_required(VERSION 3.5)

project(example_11)

# 先嘗試找看看函式庫`myMathLib`是否存在
find_package(myMathLib 1.0)
if(myMathLib_FOUND)
	include_directories(${myMathLib_INCLUDE_DIRS}) # 假如`myMathLib`存在，就把該函式庫的標頭檔路徑引入進來使用
	message(STATUS "Found the library: myMathLib")

	# 宣告變數提供給後面的指令`configure_file()`產生標頭檔，以便讓程式碼可以根據該標頭檔的巨集
	# 來判斷要使用哪一個函式庫來計算指數
	set(HAVE_MY_MATH_LIB 1) 
else()
	message(WARNING  "Not found the libray myMathLib, so we use the standard libray.")
	link_libraries(m) # 若`myMathLib`不存在，就使用`maht.h`，但在linux中使用`math.h`時需要使用這個指令連結相對應的函式庫檔
endif(myMathLib_FOUND)


# 使用樣板產生標頭檔`config.h`，以便讓在這個範例中的程式碼使用條件編譯選擇適合的函式庫計算指數
configure_file(
	${CMAKE_SOURCE_DIR}/includes/config.h.in
	${CMAKE_SOURCE_DIR}/includes/config.h)

aux_source_directory(./src Source_Files)
add_executable(exe ${Source_Files})
if(myMathLib_FOUND)
	target_link_libraries(exe myMathLib) # 假如`myMathLib`存在，就用這個指令把該函式庫連結進來
endif(myMathLib_FOUND)

