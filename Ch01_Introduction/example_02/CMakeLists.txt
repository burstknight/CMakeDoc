# 要求使用的`cmake`最低版本必須是3.0
cmake_minimum_required(VERSION 3.0)

# 設定專案的名稱為`example_02`
project(example_02)

# 這個指令可以把包含標頭檔的資料夾引入進來使用
include_directories(src)

# 把所有的`.c`檔編譯成可執行檔`myExe`
add_executable(myExe src/main.c src/calcPow.c)
