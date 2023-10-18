# Library
前一章節我們學會怎麼使用`cmake`來建置一組原始碼檔案成一個可執行檔。有時我們可能需要把原始碼編譯成函式庫，提供給別的專案使用，光靠前一章介紹的使用方式可能還不夠，接下來該介紹更進階一些的用法。

## 多目錄建置
有時候我們開發程式時，可能會把功能相近的`.cpp`或`.c`等檔案放在同一個資料夾中，方便管理。也就是說在一個專案的根目錄中，可能會有一個或多個資料夾中包含原始碼檔，而且這些資料夾可能還包含多層的子目錄。這個時候我們不太可能只用`aux_source_directory()`這個指令去搜尋所有的原始碼檔。

### 給予需要建置的子目錄: `add_subdirectory()`
這個時候我們可以使用`add_subdirectory()`這個指令，用來告訴`cmake`哪一個子目錄也有`CMakeLists.txt`。在建置的過程中，`cmake`就會進入給定的子目錄中，然後使用該子目錄的`CMakeLists.txt`來產生編譯時所需的檔案。`add_subdirectory()`的使用方式如下:
```cmake
add_subdirectory(<sub_directory>)
```

其中`<sub_directory>`這個參數就是用來包含`CMakeLists.txt`的子目錄。

### 建置程式碼為函式庫: `add_library()`
前面提到為了方便管理原始碼，會把功能相近的原始碼檔案放在同一個資料夾中，而且我們也可以使用`add_subdirectory()`這個指令進入子目錄中建置原始碼。接下來需要思考一個問題，我們要怎麼把所有子目錄的原始碼檔案編譯好，然後整合起來使用呢?

其中一種做法是把子目錄的原始檔案編譯成函式庫檔，然後再把這些函式庫檔與最終的可執行檔連結起來。`cmake`提供一個指令`add_library()`，可以把原始碼檔案編譯成函式庫，使用方式如下:
```cmake
add_library(<lib_name> [mode] <source 01> <source 02> ... <source N>)
```

這個指令有幾個參數:
* `<lib_name>`: 用來指定函式庫的名稱，而且在`CMakeLists.txt`中還會以變數的形式表示，<F3>方便把可執行檔與函式庫連結起來。
* `[mode]`: 可以選擇函式庫的種類，如果沒設定，預設會編譯成靜態函式庫。可以使用的參數值有三種:
    * `STATIC`: 會把原始碼編譯成靜態函式庫。
    * `SHARED`: 會把原始碼編譯成共享函式庫。
    * `MODULE`: 在`dyld`系統下才有效，否則與`SHARED`相同的效果。
* `<source 01> <source 02> ... <source N>`: 用來指定原始碼檔案的路徑，假如有多個項目，每個項目之間必須用空格隔開。

這裡簡單解釋一下什麼是函式庫。有時候我們開發專案時，會發現有些程式碼會在其他專案中也會用到。當我們發現這個共同的程式碼存在Bug，或是缺少某些功能時，我們就必須去修改每個專案中那些共同的程式碼才行，而且還有可能會漏掉有些專案沒改到。為了方便管理這些共同的程式碼，我們可以把這些共同的程式碼抽離出來變成一個新專案獨立管理，這個就是函式庫。

使用上函式庫主要分成兩種，也就是靜態函式庫和共享函式庫。這邊就暫時忽略`add_library()`裡提到的`MODULE`，因為這個似乎只在蘋果電腦的作業系統上才會使用。這裡整理出一個表格，可以很輕易了解這兩種函式庫的差別和使用情境。

| 		| 靜態函式庫 (Static Library) 	| 共享函式庫 (Shared Library) 	|
|-------|-------------------------------|--------------------------------
| 說明 	| 使用這種函式庫的應用程式在建置的過程中，會把整個函式庫包進來。這種函式庫的檔名通常以`lib`開頭，並且以`.a`當副檔名。 | 使用這種函式庫的應用程式，只有在程式開始運作時，才會把函式庫載進來。這種函式庫的的檔名同樣也用`lib`開頭，但是副檔名則是`.so`。 |
| 優點 	| 1. 由於編譯的過程中會把靜態函式庫包進來，所以可執行檔可以在不存在靜態函式庫的情況下正常執行。 <br> 2. 程式的執行效率會比較高 | 1. 因為共享函式庫與可執行檔完全分離，所以編譯出來的可執行檔會比較小 <br> 2. 當共享函式庫更新以後，基本上可執行檔不需要重新編譯。 |
| 缺點 	| 1. 可執行檔會非常大。 <br> 2. 當靜態函式庫更新以後，可執行檔就必須重新編譯。 | 1. 由於可執行檔在執行時需要使用到共享函式庫，所以只要缺少共享函式庫，就無法正常執行。 |

### 連結函式庫: `target_link_libraries()`
前面提到`add_library()`可以用來把一組原始碼檔案編譯成一個函式庫。既然有辦法自己產生函式庫，那也需要知道怎麼把函式庫連結起來，這樣才能夠整合出一個完整的程式。

`cmake`有提供一個指令`target_link_libraries()`，這個指令可以把函式庫連結進來，使用方式如下:
```cmake
target_link_libraries(<target> <lib 01> <lib 02> ... <lib N>)
```

這裡列出幾個重點:
* `<target>`: 這個參數用來指定想連結進來的目標檔，可以是可執行檔，也可以是函式庫。
* `<lib 01> <lib 02> ... <lib N>`: 用來給予函式庫，讓目標檔可以連結過來，假如有多個函式庫，每一個項目都要用空格隔開。

### 範例說明
接下來用範例來說明`add_subdirectory()`這個指令怎麼使用。在開始說明之前，先解釋這邊所使用的範例。這個範例的主要目標是，用C語言開發一個類似`printf()`的函數，但是這個函數可以印出有顏色的文字。因為這個範例是用來說明怎麼使用`add_subdirectory()`，所以不會特別說明範例的程式碼。

請先建立一個資料`example_08`，然後新增檔案`main.c`，該檔案的內容如下:
```c
#include "./ColorPrint/myPrint.h"

int main(){
	showMessage(Info, "Hello world!\n");

	showMessage(Error, "Error message!\n");
	return 0;
} // End of main
```

接下來請新增`CMakeLists.txt`，該檔案的內容如下:
```cmake
cmake_minimum_required(VERSION 3.5)

project(example_08)

# 要求編譯的過程中需要使用C99
set(CMAKE_C_STANDARD 99)

# 新增子目錄`ColorPrint`，要求cmake也要進入建置程式碼
add_subdirectory(ColorPrint)

aux_source_directory(. Src)
add_executable(myPrint ${Src})

# 連結函式庫`ColorPrint`
target_link_libraries(myPrint ColorPrint)
```

這邊只列出幾個重點:
* `set(CMAKE_C_STANDARD 99)`: 這一行主要用來告訴編譯器，這個範例的程式碼會用到`C99`。
* `add_subdirectory(ColorPrint)`: 這行告訴`cmake`有一個子目錄`ColorPrint`中也有`CMakeLists.txt`，所以在建置的過程中也要進入這個子目錄中。
* `target_link_libraries(myPrint ColorPrint)`: 由於子目錄`ColorPrint`中的原始碼會編譯成函式庫，所以需要用到這行讓可執行檔與函式庫連結起來。

現在該處理子目錄`ColorPrint`，請先建立一個目錄`ColorPrint`，然後在這個目錄中新增一個標頭檔`myPrint.h`，內容如下:
```c
#ifndef MY_PRINT_H
#define MY_PRINT_H

#include <stdio.h>

enum LevelMode{
	Info = 0,
	Warning,
	Error
};

/**
 * @brief Like printf() but it can show color message.
 *
 * @param mode: Set the level for the message.
 * @param pcMessage: Give teh message to show on the screen.
 * @param ...
 *
 * @return Return the number of the given message.
 */
int showMessage(enum LevelMode mode, const char* pcMessage, ...);

#endif
```

接下來請在目錄`ColorPrint`中新增`myPrint.c`，該檔案的內容如下:
```c
#include "myPrint.h"
#include <string.h>
#include <stdarg.h>

int print(const char* pcColor, const char* pcMessage, va_list args){
	int iLength = 0;

	iLength = fprintf(stdout, pcColor);

	iLength += vfprintf(stdout, pcMessage, args);

	iLength += fprintf(stdout, "\x1b[0m");

	return  iLength;
} // End of print

int showMessage(enum LevelMode mode, const char* pcMessage, ...){
	char acColor[10];
	switch (mode) {
		case Warning:
			sprintf(acColor, "\x1b[33m");
			break;
		case  Error:
			sprintf(acColor, "\x1b[31m");
			break;
		case  Info:
		default:
			sprintf(acColor, "\x1b[0m");
			break;
	} // End of switch

	va_list args, args_data;
	va_start(args, pcMessage);
	va_copy(args_data, args);

	int iLength = print(acColor, pcMessage, args);

	va_end(args);
	va_end(args_data);

	return iLength;
} // End of showMessage
```

最後請在目錄`ColorPrint`中新增`CMakeLists.txt`，該檔案的內容如下:
```cmake
aux_source_directory(. Lib_Src)

add_library(ColorPrint ${Lib_Src})
```

這邊有幾個重點:
* `aux_source_directory()`: 用來把目錄`ColorPrint`中所有的`.c`檔找出來，然後放進變數`Lib_Src`中。
* `add_library()`: 這個指令會把目錄`ColorPrint`中所有的原始碼檔都編一成一個函式庫檔，而且該函式庫的名稱為`ColorPrint`。
