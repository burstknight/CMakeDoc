cmake_minimum_required(VERSION 3.5)
project(example_13)

# 使用這個指令找出函式庫`myMathLib`的所有函式庫檔，並且儲存在變數`Libs`中
find_library(Libs myMathLib PATH /usr/local/lib/myMathLib)
include_directories(/usr/local/include/myMathLib)

aux_source_directory(./src Source_Files)
add_executable(exe ${Source_Files})

# 由於變數`Libs`已經儲存函式庫檔的資訊，所以我們可以使用`target_link_libraries()`把函式庫連結進可執行檔中
target_link_libraries(exe ${Libs})

