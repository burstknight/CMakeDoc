# Library
前一章節我們學會怎麼使用`cmake`來建置一組原始碼檔案成一個可執行檔。有時我們可能需要把原始碼編譯成函式庫，提供給別的專案使用，光靠前一章介紹的使用方式可能還不夠，接下來該介紹更進階一些的用法。

## 多目錄建置
有時候我們開發程式時，可能會把功能相近的`.cpp`或`.c`等檔案放在同一個資料夾中，方便管理。也就是說在一個專案的根目錄中，可能會有一個或多個資料夾中包含原始碼檔，而且這些資料夾可能還包含多層的子目錄。這個時候我們不太可能只用`aux_source_directory()`這個指令去搜尋所有的原始碼檔。

### 新增需要建置的子目錄: `add_subdirectory()`
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
* `<lib_name>`: 用來指定函式庫的名稱，而且在`CMakeLists.txt`中還會以變數的形式表示，方便把可執行檔與函式庫連結起來。
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

### 引入標頭檔位置: `include_directories()`
當我們開發一個專案需要用到函式庫的時候，就需要使用這個指令告訴`cmake`，這個專案應該去哪裡找函式庫的標頭檔。這個指令的用法如下:
```cmake
include_directories(<include_files_directory>)
```

這個指令的參數意義如下:
* `<include_files_directory>`: 用來表示一個目錄的路徑，這個目錄會存放一個專案需要使用的標頭檔。

基本上，假如我們開發的專案需要使用的標頭檔都在該專案的資料夾中，其實可以不需要使用這個指令。如果我們開發的專案使用到第三方函式庫，比方說使用`opencv`，就需要使用這個指令。

### 範例說明
接下來用範例來說明`add_subdirectory()`這個指令怎麼使用。在開始說明之前，先解釋這邊所使用的範例。這個範例的主要目標是，用C語言開發一個類似`printf()`的函數，但是這個函數可以印出有顏色的文字。因為這個範例是用來說明怎麼使用`add_subdirectory()`，所以不會特別說明範例的程式碼。

在開始說明範例之前，先說一下稍後提到的範例的一些細節。基本上這個範例是從`example_04`改過來，我們這次的目標是把`myMathLib.c`和`myMathLib.h`當做一個函式庫來使用。此外，`main.c`不屬於這個函式庫，所以在建置的時候我們應該要分兩階段來編譯程式碼:
1. 先編譯`myMathLib.c`成一個函式庫檔`libmyMathLib.a`
2. 把`main.c`和函式庫檔`libmyMathLib.a`編譯成一個可執行檔。

現在我們就用範例說明怎麼用階段式編譯程式碼。請先建立一個資料夾`example_08`，然後在這個資料夾中建立一個目錄`includes`，這個目錄主要用來放一個專案中所有的標頭檔。請在這個目錄中新增一個標頭檔`myMathLib.h`，該檔案的內容如下:
```c
#ifndef MY_MATH_LIB_H
#define MY_MATH_LIB_H

/**
 * @brief Calculate pow.
 *
 * @param dX: Give a number to calculate the power.
#include "../../includes/myMathLib.h"

double calcPow(double dX, int iExp){
	double dResult = 1.0;
	int i = iExp;

	while (1) {
		if (i == 0) {
			break;
		}else if (i > 0) {
			dResult *= dX;
			i--;
		}else {
			dResult /= dX;
			i++;
		} // End of if-condition
	} // End of while-loop

	return dResult;
} // End of calcPow
 
 * @param iExp: Give the exponential.
 *
 * @return 
 */
double calcPow(double dX, int iExp);

#endif
```

接下來請在`example_08`中在建立一個目錄`src`，這個目錄主要用來放置一個專案中所有`.c`或`.cpp`檔。現在我們需要在`src`中再建立一個子目錄`myMathLib`，這個子目錄會放置函式庫`myMathLib`的`.c`檔，接下來請在子目錄`myMathLib`中新增檔案`myMathLib.c`，該檔案的內容如下:
```c
#include "../../includes/myMathLib.h"

double calcPow(double dX, int iExp){
	double dResult = 1.0;
	int i = iExp;

	while (1) {
		if (i == 0) {
			break;
		}else if (i > 0) {
			dResult *= dX;
			i--;
		}else {
			dResult /= dX;
			i++;
		} // End of if-condition
	} // End of while-loop

	return dResult;
} // End of calcPow
 
```

既然子目錄`myMathLib`已經新增`.c`檔，接下來就該編輯`CMakeLists.txt`把`myMathLib.c`編譯成函式庫檔。請在子目錄`myMathLib`中新增檔案`CMakeLists.txt`，該檔案的內容如下:
```
# 在當前的資料夾中找出所有的`.c`檔
aux_source_directory(. Lib_Source_Files)

# 把所有原始碼檔案編譯成static library，而且該函式庫的名稱為`myMathLib`
add_library(${Lib_Name} ${Lib_Source_Files})
```

在這個檔案中只有兩行指令:
1. 先透過`aux_source_directory()`把子目錄`myMathLib`中所有`.c`檔都找出來，並且儲存在變數`Lib_Source_Files`中。
2. 使用`add_library()`把子目錄`myMathLib`中所有的`.c`檔編譯成靜態函式庫。

為了讓`cmake`能夠進入子目錄`myMathLib`中編譯出靜態函式庫，我們需要在目錄`src`中新增`CMakeLists.txt`，該檔案的內容如下:
```cmake
# 進入子目錄`myMathLib`，處理該子目錄中的`CMakeLists.txt`
add_subdirectory(./myMathLib)
```

這個檔案只有一行指令。我們透過`add_subdirectory()`要求`cmake`進入在目錄`src`中的子目錄`myMathLib`，處理該子目錄中的`CMakeLists.txt`，以便能把該子目錄的`.c`檔都編譯成函式庫檔。

我們已經處理好編譯函式庫的部分，接下來該新增`main.c`來使用這個函式庫。請先在目錄`src`中新增檔案`main.c`，該檔案的內容如下:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/myMathLib.h"

int main(int argc, char** argv){
	if (argc < 3) {
		printf("Usage: %s base exponential\n\tbase\t\tGive a float number as the base.\n\texponential\tGive an integer as the exponential.\n", argv[0]);
		exit(1);
	} // End of if-condition

	double dBase = atof(argv[1]);
	int iExp = atoi(argv[2]);

	printf("%.4f ^ %d = %.4f\n", dBase, iExp, calcPow(dBase, iExp));

	return 0;
} // End of main
```

最後請在資料夾`example_08`中新增檔案`CMakeLists.txt`，該檔案的內容如下:
```cmake
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
```

在這個檔案中，前兩個指令就不解釋，我們就針對後面的部分列出幾個重點:
* `include_directories(./includes)`: 這行用來指定標頭檔都放在目錄`includes`中。其實沒有這一行也可以建置，因為`myMathLib`本來就包含在這個專案裡面。
* `set(Lib_Name myMathLib)`: 我們使用這個指令宣告變數`Lib_Name`，用來指定函式庫的名稱。
* `add_subdirectory()`: 我們透過這個指令讓`cmake`進入目錄`src`中編譯函式庫`myMathLib`。
* `aux_source_directory()`: 透過這個指令把目錄`src`中的`main.c`找出來，然後使用`add_executable()`編譯成可執行檔`myExe`。
* `target_link_libraries()`: 為了讓可執行檔`myExe`可以使用函式庫`myMathLib`，我們需要使用這個指令把該函式庫連結進來。

這邊稍微解釋一下，為什麼`add_executable()`不是寫在目錄`src`中的`CMakeLists.txt`中，而是寫在根目錄的`CMakeLists.txt`中。當我們把`add_executable()`放在目錄`src`中的`CMakeLists.txt`，就會發現可執行檔編譯完以後，會放在`build`資料夾中的目錄`src`中。我們希望最終的可執行檔`myExe`放在資料夾`build`中，所以`add_executable()`這個指令就應該放在根目錄的`CMakeLists.txt`中。

## 使用自訂編譯選項
有時候我們可能需要根據實際的情況調整編譯選項。比方說有一台開發用的電腦比較老舊，可能無法使用某個函式庫，這個時候就可以調整編譯選項，使用替代的函式庫，至少讓開發的城市勉強可以運作。

`cmake`也有提供自訂編譯選項，這裡提供其中一種做法。這個做法大致上來說步驟如下:
1. 先在專案中建立一個檔案`config.h.in`，並且在這個檔案中。
2. 編輯專案中需要使用`config.h`這個標頭檔的所有檔案，透過`#ifdef`、`#ifndef`等巨集來條件編譯。
3. 編輯`CMakeLists.txt`:
    1. 使用指令`option()`新增編譯選項。
    2. 透過指令`configure_file()`產生`config.h`。
    3. 使用`if()`來做相對應的條件判斷。

### 產生設定標頭檔: `configure_file()`
`configure_file()`這個指令的主要功能是，可以根據使用者設定編譯選項來產生相對應內容的標頭檔，一個專案的程式碼就會讀取這個標頭檔，並且依據巨集是否存在來達成條件編譯。使用方式如下:
```cmake
configure_file(<source_config_path> <target_config_path>)
```

這個指令的參數定義如下:
* `<source_config_path>`: 用來指定`config.h.in`這個檔案的所在路徑。
* `<target_config_path>`: 用來指定產生相對應的檔案路徑。

原則上參數`<source_config_path>`所指定的檔案應該也可以是別的檔名，也不一定要`config.h.in`，只是習慣上可能會比較常使用`config.h.in`。重點還是在於這個檔案必須遵守`cmake`定義的撰寫方式，建置的過程中才會產生相對應的輸出標頭檔。

`config.h.in`這類的檔案都會以`.h.in`當副檔名，一般都會使用以下的方式定義巨集:
```c
#cmakedefine <macro_var> ...
```

這裡有幾個重點:
* `#cmakedefine`: 這是`cmake`定義的巨集，功能上類似於C語言的`#define`，可以拿來宣告巨集。
* `<macro_var>`: 用來指定巨集的名稱。
* `...`: 這個意思是如果有需要可以給予一個值，類似於`#define VAR 0`，當然也可以不給值。

### 定義編譯選項: `option()`
接下來介紹一下`option()`，這個指令的功能是定義出一個編譯選項，並且使用變數來儲存該編譯選項，其值會是一個布林值。使用方式如下：
```cmake
option(<var> <message> [<value>])
```

這個指令的參數意義如下:
* `<var>`: 可以用來指定變數名稱。
* `<message>`: 可以給予提示文字，方便讓使用者了解這個編譯選項的用意。
* `[<value>]`: 用來指定預設值，可以是`ON`或是`OFF`。假如沒有給，預設會是`OFF`。

### 範例說明
現在用範例來說明怎麼使用`configure_file()`和`option()`這兩個指令。請先建立一個新的資料夾，該資料夾的名稱為`example_09`。其實這個範例是從前一個範例`example_08`去更改，也可以直接把`example_08`複製過來使用。接下來要說明的範例主要的目標是，透過在`CMakeLists.txt`新增編譯選項，來決定`main.c`是要使用我們自己寫的函式庫`ColorPrint`，還是使用`stdio.h`的`printf()`。

請先在資料夾`example_09`中新增檔案`main.c`，內容如下:
```c
#include "config.h"
#ifdef USE_COLOR_PRINT
	#include "./ColorPrint/myPrint.h"
#else
	#include <stdio.h>
#endif

int main(){
#ifdef USE_COLOR_PRINT
	showMessage(Info, "Hello world!\n");
	showMessage(Error, "Error message!\n");
#else
	printf("Hello world!\n");
	printf("Error message!\n");
#endif

	return 0;
} // End of main
```

與範例`example_08`不同之處有:
* 第一行多了`#include "config.h"`，而且需要注意一點，我們不需要新增`config.h`這個標頭檔，因為之後會透過`cmake`幫我們產生。
* 在函數`main()`前面使用條件編譯與巨集`USE_COLOR_PRINT`，根據我們是否需要使用我們自己寫的函式庫`ColorPrint`與否，來決定要使用哪一個標頭檔。
* 在函數`main()`裡面也同樣使用條件編譯和巨集`USE_COLOR_PRINT`，來決定是否要使用我們自己寫的函式庫。

接下來請新增檔案`CMakeLists.txt`，該檔案的內容如下:
```cmake
cmake_minimum_required(VERSION 3.5)

project(example_09)

set(CMAKE_C_STANDARD 99)

# 新增一個建置的設定，可選擇是否要使用`ColorPrint`這個函式庫
option(USE_COLOR_PRINT "Use color print lib" ON)

# 用來處理建置的設定標頭檔
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
	)

# 透過`if()`決定是否要使用`ColorPrint`
if(USE_COLOR_PRINT)
	include_directories("${PROJECT_SOURCE_DIR}/ColorPrint")
	add_subdirectory(ColorPrint)
	set(Extra_Libs ${Extra_Libs} ColorPrint)
endif(USE_COLOR_PRINT)

aux_source_directory(. Src)
add_executable(myPrint ${Src})
target_link_libraries(myPrint ${Extra_Libs})
```

這裡有幾個重點:
* `option(USE_COLOR_PRINT "USE_COLOR_PRINT" ON)`: 新增編譯選項，所以我們可以使用`if()`根據編譯選項`USE_COLOR_PRINT`是否開啟，做不同的事情:
	* 假如`USE_COLOR_PRINT`為`ON`: 就編譯函式庫`ColorPrint`，然後使用`set()`這個指令宣告變數`Extra_Libs`，方便我們在編譯最終的可執行檔時，可以幫函式庫連結進來。
	* 假如`USE_COLOR_PRINT`為`OFF`: 不會編譯函式庫`ColorPrint`，而且最終的可執行檔`myPrint`就直接使用`stdio.h`的`printf()`。
* `configure_file()`: 我們透過`configure_file()`要求`cmake`讀取`config.h.in`，產生標頭檔`config.h`，並且根據編譯選項`USE_COLOR_PRINT`來決定該標頭檔是否需要宣告巨集`USE_COLOR_PRINT`。

現在就新增檔案`config.h.in`，該檔案的內容如下:
```c
#cmakedefine USE_COLOR_PRINT
```

這邊透過由`cmake`提供的`#cmakedefine`宣告巨集`USE_COLOR_PRINT`。

至於`ColorPrint`這個資料夾，因為在這個範例中主要是透過新增編譯選項，讓`main.c`決定是否要使用`ColorPrint`的函式，所以該資料夾的檔案內容與範例`example_08`沒有什麼不同。因此，這邊就不另外贅述了。

現在請先使用下面的指令建立出資料夾`build`，並且在該資料夾中建置範例`example_009`:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

當我們使用`cmake ..`這個指令時，會在資料夾`build`中產生出`makefile`和編譯時所需的檔案。此外，因為我們在`CMakeLists.txt`中使用到`configure_file()`，所以我們可以看到該範例中會多出`config.h`這個標頭檔。由於我們使用的指令`option()`新增的編譯選項`USE_COLOR_PRINT`，預設值為`ON`，所以`config.h`的內容為:
```c
#define USE_COLOR_PRINT
```

因為`USE_COLOR_PRINT`為`ON`，標頭檔`config.h`就宣告出同名的巨集，所以`main.c`就會使用函式庫`ColorPrint`。當我們在資料夾`build`中使用`make`這個指令編譯時，就會發現最終編譯出來的可執行檔確實會使用函式庫`ColorPrint`印出有顏色的文字。

假如我們不想開啟`USE_COLOR_PRINT`使用函式庫`ColorPrint`，該怎麼做才好呢?有兩個做法可以使用:
1. 先使用`cmake`產生編譯需要的檔案，然後使用`ccmake`關閉`USE_COLOR_PRINT`。
2. 使用`cmake`產生`makefile`的時候給予參數，關閉`USE_COLOR_PRINT`。

這兩種使用方式都可以關閉`USE_COLOR_PRINT`，差別在於使用情境。如果一個專案中已經先使用`cmake ..`在`build`資料夾中產生編譯所需的檔案，就會使用第一種作法。假如專案中還沒使用`cmake`產生編譯所需的檔案，就可以使用第二種作法。

既然已經在`build`中透過`cmake ..`產生`makefile`，我們先試試使用第一種作法。`ccmake`是一個文字介面的工具，我們可以在終端機中透過這個工具調整編譯的選項，但是要注意一點，必須先使用`cmake`這個指令產生出編譯所需的檔案，才能夠使用`ccmake`。現在請先在終端機中透過指令`cd`切換工作目錄到`build`中，然後使用下面的指令:
```bash
$ ccmake ..
```

由於我們的當前工作目錄是`build`，而`CMakeLists.txt`在上一層的目錄中，所以我們需要在`ccmake`後面加上參數`..`，`ccmcake`才能夠取得編譯選項提供給我們調整。當我們使用`ccmake ..`時，會看到終端機出現一個使用者介面。在這個使用這介面中可以使用方向鍵的上下鍵或是`j`和`k`來移動游標，並且可以在想更改的選項上按下`Enter`鍵來修改。

現在請用方向鍵或`j`和`k`移動游標到`USE_COLOR_PRINT`，並且按下`Enter`鍵。這個時候會發現`USE_COLOR_PRINT`原本是`ON`，更改後會變成`OFF`。接下來請按`c`鍵，這個時候`ccmake`就會根據當前的設定重新建置一次，然後按`q`鍵離開。

如果我們去看`config.h`，就會發現這個標頭檔的內容更改了:
```c
/* #undef USE_COLOR_PRINT */
```

可以看到`config.h`沒有宣告巨集`USE_COLOR_PRINT`，這是因為我們透過`ccmake`關掉`USE_COLOR_PRINT`並且重新建置一次。假如我們編譯一次程式碼，也會發現最終編譯出的可執行檔也同樣不使用`ColorPrint`，而是使用`stddio.h`的`printf()`。

現在我們來試試第二種方法，請先確認當前的工作目錄是`build`，然後使用下面的指令清除`build`中所有的檔案:
```bash
$ rm -rf *
```

接下來請使用下面的指令在資料夾`build`中建置出編譯所需的檔案:
```bash
$ cmake .. -DUSE_COLOR_PRINT=OFF
```

這邊解釋一下，`cmake`這個指令後面接上參數`-DUSE_COLOR_PRINT=OFF`，可以將編譯選項`USE_COLOR_PRINT`更改成`OFF`。基本上只要在`cmake`後面加上參數`-D`，就可以更改編譯選項。

我們可以看到`config.h`也同樣不會宣告巨集`USE_COLOR_PRINT`，而且編譯以後也會發現最終可執行檔也同樣不會使用`ColorPrint`。

