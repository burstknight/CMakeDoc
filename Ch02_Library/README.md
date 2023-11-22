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

----

## 單元測試
試想一個情況，我們先為一個專案開發十個類別，這十個類別會整合起來實現一個功能。我們在開發這十個類別的過程中，沒有先測試每個類別的運作是否正確，而是等到十個類別都實作完畢並且整合起來以後才測試。問題來了，我們在測試整合後的程式碼，發現程式執行結果不正確，唯一可以確定的是這十個類別中至少有一個可能有BUG，可是我們要怎麼找出哪一個類別有BUG？

我們很有可能會花費大量的時間去檢查這十個類別，運氣好的話或許只需要幾個小時以內就找到問題點，但是運氣不好的話，說不定花個好幾天都可能找不到原因。有些BUG有可能不只一個類別有問題，甚至有些BUG還是在整合以後才會出現。這些情況都會導致解決BUG


針對剛剛提到的情境，單元測試就是一個很好的解決辦法。單元測試的概念是，在完成一個專案的每一個類別或函式以後，就額外寫一個測試程式，測試看看剛完成的類別和函式是否有BUG。因為只針對單一的類別和函式測試，所以測試的範圍會比較小，只要測試失敗時，就可以很輕易找出問題出在哪裡。此外，在把多個類別和函式整合起來時，也需要寫測試程式，測試看看在整合以後是否會出現不如預期的錯誤。

有很多種方式可以做單元測試，比方說使用別人寫好的框架去寫測試程式，像是[google test](https://github.com/google/googletest)。這邊介紹一個更簡單的做法，那就是使用`ctest`來幫我們測試程式碼是否寫正確。如果真要說的話，`cmake`算一個專門用來建置專案的整合軟體，它除了包含我們一直都在使用的工具`cmake`以外，還有其他用來輔助我們開發專案的工具，`ctest`就是其中一個工具。

在介紹怎麼使用`ctesst`做單元測試以前，先說明`ctesst`是如何做到單元測試。假設我們有一個程式，下面是這個程式碼的原始碼:
```c
#include <stdio.h>

int main(int argc, char** argv){
	if(argc < 2){
		printf("Error: Useage: %s <your_name>\n", argv[0]);
		return 1;
	} // End of if-condition

	printf("Hello, %s!\n, argv[1]);

	return 0;
} // End of main
```

這個程式的功能為，下指令時順便傳入一個參數當作使用者名稱，然後印出文字。假設這個程式碼檔名是`main.c`，我們可以使用下面的指令編譯成可執行檔`hello`:
```sh
$ gcc main.c -o hello
```

這個時候會發現當前目錄中會多出檔案`hello`，這個檔案就是剛剛編譯出來的可執行檔。當我們使用這個可執行檔時，會有兩種情況:
* 程式執行成功，並且印出文字。
* 程式執行失敗，然後印出錯誤訊息。

我們先從執行成功開始說明。當我們使用指令`./hello Bob`時，程式會這樣運作:
1. 函式`main()`會把指令`./hello Bob`當成字串並且用空格切成`./hello`與`Bob`這兩個字串，然後以字串陣列的方式來儲存到參數`argv`中。
2. 因為參數`argv`有兩個字串，所以參數`argc`會是`2`。因此，程式不會執行`if`裡面的指令，而是執行`printf("Hello, %s!", argv);`，然後我們就會在終端機上看到`Hello, Bob!`這段文字。
3. 最後執行`return 0;`這個指令，回傳0。

接著，我們來分析當程式執行失敗時會怎麼運作。當我們使用指令`./hello`時，程式會這樣運作:
1. 函式`main()`會把指令`./hello`當成字串處理，由於這個字串沒有任何空格，所以無法切割成多個字串，只能直接當成一個只有一個元素的字串陣列儲存進參數`argv`中。
2. 由於參數`argv`只有一個元素`./hello`，所以參數`argc`會是`1`。因此，程式會執行`if`裡面的指令，也就是執行`printf(Error: Usage: %s <your_name>\n, argv[0]);`，然後我們就會在終端機上看到印出來的錯誤訊息。
3. 最後程式會執行`return 1;`，在回傳1當回傳值以後，程式就會執行完畢。

我們可以從這兩種情況的運作流程中發現一個共通點，那就是不管程式執行結果是否成功，都會使用`return`回傳一個數值。習慣上程式運作成功時會回傳0，而程式運作失敗時則回傳非0的數值。在`bash`中我們可以在跑完一個程式以後使用指令`echo $?`確認該程式的回傳值。當我們先使用`./hello Bob`以後，會發現指令`echo $?`會顯示0，但是當我們使用`./hello`時會因為程式的執行結果是失敗的，所以使用指令`echo $?`則會顯示1。

回到原本的問題，我們該如何使用`ctest`來做單元測試?這個問題相當簡單，那就是判斷一個程式的回傳值是否為0。一般來說只要回傳值為0，就表示這個測試算成功，而回傳值不為0則表示測試失敗。當然實際在測試時沒有這麼簡單，因為某些情況下我們們故意讓一個測試失敗，來確認在失敗的情況下能否顯示正確的錯誤訊息和錯誤處理，這個時候我們就應該預期測試程式的回傳不為0。
