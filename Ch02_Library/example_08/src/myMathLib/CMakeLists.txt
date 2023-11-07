# 在當前的資料夾中找出所有的`.c`檔
aux_source_directory(. Lib_Source_Files)

# 把所有原始碼檔案編譯成static library，而且該函式庫的名稱為`myMathLib`
add_library(${Lib_Name} ${Lib_Source_Files})
