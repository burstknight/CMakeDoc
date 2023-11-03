cmake_minimum_required(VERSION 3.5)

project(example_08)

# 設定標頭檔所在的位置
include_directories(./includes)

# 宣告變數`Lib_Name`為`myMathLib`，作為函數庫的名稱
set(Lib_Name myMathLib)

# 進入子目錄`src`中處理該子目錄的`CMakeLists.txt`
add_subdirectory(./src)

aux_source_directory(./src Source_Files)

add_executable(myExe ${Source_Files})

# 把函數庫`myMathLib`連結進可執行檔中
target_link_libraries(myExe ${Lib_Name})
