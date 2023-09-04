# Ch02 CMake
在上一個章節中有提到，`cmake`是一個專門產生建置工具所需設定檔的軟體，為了能夠產生正確的檔案，就需要編輯好`CMakeLists.txt`這個檔案。就跟`makefile`類似，`CMakeLists.txt`裡面的內容也有自己獨特的語法，就像一種程式語言。這種程式語言有幾個特性:
* 每一個指令都像函數
* 每個指令沒有大小寫之分
* 可以宣告變數，但是變數有大小寫之分

----

## 變數
在`CMakeLists.txt`中也可以宣告變數，讓我們可以寫出更易讀又有彈性的`CMakeLists.txt`，也可以避免打錯字。

### set()與message()
前面提到在`CMakeLists.txt`中變數有大小寫之分，接下來實際體驗看看。這邊對應的範例是`example_03`。

先從指令`set()`說起，當一個變數不存在時，這個指令就可以用來宣告變數。假如有一個變數已經存在了，這個指令可以用來修改該變數的值。
```
set(<var> <value>)

說明:
<var>: 給予變數的名稱
<value>: 給予該變數的值
```

為了能夠在範例`example_03`中方便說明，這邊先介紹指令`message()`。這個指令的功能很類似`C`語言中的`printf()`，可以把變數和字串印出來。有時透過`cmake`建置專案時，需要顯示一些提示用的訊息，或是因某些因素導致建置失敗時也需要顯示錯誤訊息，這個時候就會用到這個指令。
```
message([<mode>] <msg> ...)

說明:
<mode>: 用來指定顯示的訊息的等級
<msg>: 給予欲顯示的資訊
```
比較值得一提的是，`<mode>`這個參數也可以不給予，但是`message()`會使用預設等級來顯示資訊。這邊列出我個人認為比較常使用的等級:
| 等級          | 說明                              
|---------------|-----------------------------------
| `STATUS`      | 這個等級通常用在顯示大部分對使用者來說感興趣的訊息
| `WARNING`     | 這個等級用來顯示警告訊息
| `FATAL_ERROR` | 使用這個等級會顯示完訊息以後，強制終止後面的指令

現在就從範例中更進一步說明怎麼使用變數，請先建出一個資料夾`example_03`，然後在這個資料夾中新增一個檔案`CMakeLists.txt`。為了方便解釋，這次會一個階段一個階段說明。請先在`CMakeLists.txt`中新增下面的內容:
```cmake
cmake_minimum_required(VERSION 3.0)
project(example03)

set(Var 2.0)
set(var 55)
set(s1 "Hello world")
```
第一行是設定最低要求的`cmake`版本，而第二行則是設定專案名稱為`example03`。這邊的重點在後面的三行:
* `set(Var 2.0)`: 由於前面沒宣告變數`Var`，所以這行指令會宣告出變數`Var`，並且將其初始化為`2.0`。
* `set(var 55)`: 這行也是宣告變數`var`，並且將其值設定為`55`。
* `set(s1 "Hello world")`: 這行也是宣告變數`s1`，並且給予一個字串。

接下來請在`CMakeLists.txt`後面新增下面的內容:
```cmake
message("====================================================")

message("var: " ${var})
message("Var: " ${Var})
message("s1: " ${s1})

set(var 88)
message("Change var: " ${var})
```
這部分的第一行就只是印出分隔符號而已，方便看後面顯示的訊息。接下來的三行就是用`message()`把前面宣告的變數印出來，可以看到只要變數宣告出來，就可以使用`${}`把變數包起來，就能取出該變數的值，像是`${var}`就能取出其值`55`。最後面的那兩行會把變數`var`的值更改為`88`，然後印出來。這邊可以驗證前面提到跟變數有關的幾件事:
* 從`var`與`Var`的值不同，可以知道在`CMakeLists.txt`中的變數有大小寫之分。
* 當變數已經宣告出來時，`set()`就只會針對給定的變數修改其值。

最後請在`CMakeLists.txt`再加上下面的內容:
```cmake
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})

message("====================================================")
```
在這部分中最後一行也只是印出分隔符號而已。前面幾行則是顯示`cmake`所定義的變數的內容。`cmake`已經事先定義好非常多變數，有了這些變數，我們在`CMakeLists.txt`中不需要寫過多指令，`cmake`就能夠執行完整的建置過程。這邊先列出上面範例中出現的變數所代表的意義:
變數名稱                    | 說明
----------------------------|---------------------------------------------------
`PROJECT_SOURCE_DIR`        | 用來代表一個專案的根目錄
`PROJECT_BINARY_DIR`        | 用來代表執行指令`cmake`所在之目錄
`CMAKE_CURRENT_SOURCE_DIR`  | 用來代表當前處理`CMakeLists.txt`所在的路徑
`CMAKE_SYSTEM_PROCESSOR`    | 用來代表執行指令`cmake`之電腦的CPU類型
`CMAKE_SYSTEM_NAME`         | 用來表示執行指令`cmake`之電腦所使用的作業系統

下面是在範例`example_03`中的`CMakeLists.txt`完整的內容:
```cmake
cmake_minimum_required(VERSION 3.0)
project(example03)

set(Var 2.0)
set(var 55)
set(s1 "Hello world")

message("====================================================")

message("var: " ${var})
message("Var: " ${Var})
message("s1: " ${s1})

set(var 88)
message("Change var: " ${var})

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})

message("====================================================")
```

### 列舉所有原始碼檔案: `aux_source_directory()`
這邊再介紹一個我個人認為很好用又很常用的指令，那就是`aux_source_directory()`。

在說明這個指令之前，先來想像一個情境，假設有個專案`myProject`，在這個專案中有個目錄`src`會放置所有的原始碼。假如這個專案非常大，在目錄`src`中有幾十個檔案，編輯`CMakeLists.txt`來建置這個專案時就會非常痛苦，因為要一個一個列出`.c`或`.cpp`檔，才能編譯這些檔案，而且只要一不小心很有可能打錯字。

遇到這種狀況，最好的做法是讓`cmake`自動搜尋所有的`.c`和`.cpp`檔，然後使用這些檔案來建置專案。這麼做不僅可以避免不小心打錯字，而且不管在專案中新增或移除多少個Source code，我們只需要稍微修改`CMakeLists.txt`，就能夠建置專案。

`aux_source_directory()`這個指令在前面提到的情境中非常好用。這個指令的功能是給定一個資料夾的路徑，會找出該資料夾中所有的`.c`和`cpp`檔，然後儲存進一個變數中。
