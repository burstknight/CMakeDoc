# Introduction
在本章節中會介紹什麼是`CMake`，以及一些最基本的用法。

## 什麼是`CMake`?
`CMake`是一個用來建置專案的輔助工具，功能很類似`make`。使用`CMake`建置專案時，會需要先編輯一個叫`CMakeLists.txt`的檔案，然後使用指令`cmake`來建置。如果想知道更多細節，可以看看[維基](https://zh.wikipedia.org/zh-tw/CMake)和[CMake官網](https://cmake.org/)，上面也會更詳細的資訊。

----

## 為什麼需要使用`CMake`?
### 使用指令編譯
假設有一個專案`myProject`，在這個專案中只有一個檔案`main.c`，其內容如下：
```c
#inclucde <stdio.h>

int main(){
	printf("Hello world!\n");

	return 0;
}
```
我們可以使用`gcc`下指令來編譯該專案的`main.c`:
```sh
gcc main.c -o hello
```
這個時候專案`myProject`中就會多出一個編譯後的可執行檔`hello`。

如果開發的專案裡只有兩三個檔案，使用上面說的方法下指令來建置專案可能還行。可是假如專案中的檔案一多，比方說可能有十幾個檔案好了，還用剛剛說的方法下指令來編譯專案中所有的原始碼，這段編譯的指令肯定會非常長。開發一個大型專案，這種作法是不僅很麻煩也不太可行，所以才會需要使用一些輔助工具來管理專案，把專案中的原始碼編譯成函式庫或可執行檔。

### 使用指令make編譯
`make`也是一個用於建置專案的工具，這套工具需要使用一個腳本檔案來編寫建置的規則和流程，這個腳本檔案可以命名為`makefile`或`Makefile`。為了方便說明，這裡統一使用`makefile`。只要編寫好建置規則和流程，`make`就會根據`makefile`的內容，以及專案中每個原始碼的檔案之間的相依關係，來編譯所有的原始碼。

使用`make`建置的好處是，在編譯的過程中會根據`makefile`的規則檢查哪些檔案已經修改過且需要再編譯一次，又有哪些檔案沒更動過且不需要再編一次。這對於大型專案來說，可以節省不少編譯的時間，因為只要曾編譯過一次，`make`就只會針對更改過的檔案或新增的檔案編譯，不需要對專案中所有的檔案重新編譯。

#### example01
接下來用範例來簡單說明怎麼使用`make`來建置一個專案。這邊建議是照著下面的流程玩過一遍會比較好，假如懶得做一遍，可以直接用[example01](./example1/README.md)。

請先建一個資料夾，該資料夾的名稱可以任意使用，這邊就用`example01`來命名，後面說明比較能統一。在資料夾`example01`中再建一個資料夾，請將該資料夾命名為`src`。資料夾`src`用來放所有的source code，這包含`.c`、`.cpp`、`.h`和`.hpp`這些檔案。也因為資料夾`src`主要用來放source code，所以這個資料夾也可以稱為`Source Tree`。

##### 新增標頭檔`calcPow.h`
接下來請在資料夾`src`中新增一個標頭檔`calcPow.h`，該檔案的內容如下:
```c
#ifndef CALCPOW_H
#define CALCPOW_H

/**
 * @brief Calculate pow.
 *
 * @param dX: Give a number to calculate the power.
 * @param iExp: Give the exponential.
 *
 * @return 
 */
double calcPow(double dX, int iExp);

#endif
```
在這個標頭檔中只宣告了一個函數`calcPow()`，其實這個函數就只是簡單實作數學函式`pow()`。

##### 新增檔案`calcPow.c`
請在資料夾`src`中再新增一個檔案`calcPow.c`，用來實作函數`calcPow()`，該檔案的內容如下：
```c

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

##### 新增`main.c`
接下來該在資料夾`src`中新增`main.c`，這樣才能使用函數`calcPow()`，該檔案的內容如下：
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcPow.h"

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

##### 新增`makefile`
接下來該編輯`makefile`了。請先在目錄`example01`中新增檔案`makefile`，該檔案的內容如下:
```make
SRC_DIR := ./src
BIN_DIR := ./build
TARGET := myPow

CFLAGS := 
CC := gcc

.PHONY: all clean

all: $(BIN_DIR)/calcPow.o
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(BIN_DIR)/calcPow.o -o $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/calcPow.o:
	mkdir -p $(BIN_DIR)
	$(CC) -c $(CFLAGS) $(SRC_DIR)/calcPow.c -I$(SRC_DIR) -o $@

clean:
	rm -rf $(BIN_DIR)/*
```

這裡稍微解釋一下上面的`makefile`的內容。`makefile`中的指令也可以當作是一種程式語言，它有自己的語法。為了方便說明，上面的`makefile`的內容可以拆成兩個部分。

先從第一部分開始說起，第一部分的內容如下：
```make
SRC_DIR := ./src
BIN_DIR := ./build
TARGET := myPow

CFLAGS := 
CC := gcc
```
這部分可以看做是在宣告變數，所以這裡總共宣告了五個變數:
1. 宣告變數`SRC_DIR`，其內容為`./src`，用來設定專案`example01`中所有的source code都放在哪一個資料夾中
2. 宣告變數`BIN_DIR`，其內容為`./build`，用來指定在編譯的過程中所產生的檔案要放在哪個資料夾中
3. 宣告變數`TARGET`，其內容為`myPow`，用來指定最終會編譯出名為`myPow`的可執行檔
4. 宣告變數`CFLAGS`，用來追加編譯的參數，這個後面會解釋怎麼使用
5. 宣告變數`CC`，其內容為`gcc`，用來指定使用`gcc`來編譯程式碼
如果想取用這些變數的值，可以使用`$()`把變數包在裡面。比方說如果想取得變數`TARGET`，就可以用`$(TARGET)`來取得其值`myPow`。

在說明第二部份以前，先從怎麼在`makefile`中寫指令來編譯程式碼。在`makefile`中通常會用下面的的架構，來定義編譯的規則:
```make
<target>: <requirements>
    <command 01>
    <command 02>
    ...
    <command N>
```
接下來說明這個架構每一個意義:
* `<target>`: 它可以是一個標籤，也可以用來代表一個或一組source code編譯後的檔案名稱。
* `<requirements>`: 如果`<target>`是欲編譯的目標檔，則`<requirements>`則是用來表示編譯該目標檔所需的相依檔。假如相依檔的數量不只一個，就需要用空格隔開。
* `<command 01>`: 為了能建置專案中所有的source code，用來指定需要執行的shell指令，需要注意一點，在`<target>`底下的每行指令前面必須使用`TAB`鍵縮排才行。

第二部分的內容如下：
```make
.PHONY: all clean

all: $(BIN_DIR)/calcPow.o
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(BIN_DIR)/calcPow.o -o $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/calcPow.o:
	mkdir -p $(BIN_DIR)
	$(CC) -c $(CFLAGS) $(SRC_DIR)/calcPow.c -I$(SRC_DIR) -o $@

clean:
	rm -rf $(BIN_DIR)/*
```
接下來說明第二部分的內容。先從`.PHONY: all clean`開始說明，這一行用來告訴`make`在`makefile`中的`all`和`clean`只是標籤。`make`也可從這一行知道，使用這個`makefile`建置專案時有兩個動作可以使用:
 1. `make all`: 可以把專案`example01`建置成可執行檔`myPow`。
 2. `make clean`: 可以清除所有建置出來的檔案。

為了方便說明第二部分後面的內容，我們就透過`make`建置的流程來說明:
1. 在shell中下指令`make all`時，`make`就會執行標籤`all`這邊的指令。
2. 在執行`all`這個標籤底下的指令以前，必須先把相依檔`$(BIN_DIR)/calcPow.o`編譯出來，所以`make`就會去執行標籤`$(BIN_DIR)/calcPow.o`的指令。
3. 因為標籤`$(BIN_DIR)/calcPow.o`沒有相依檔，所以直接執行下面的兩行指令:
    1. 先建立出目錄`build`。
    2. 把資料夾`src`中的`calcPow.c`編譯成`calcPow.o`，並且把產生出來的檔案存放到目錄`build`中。
4. 因為建置成可執行檔所需的相依檔`calcPow.o`已經編譯出來，所以回到標籤`all`，繼續執行在標籤`all`下面的指令，把可執行檔`myPow`編譯出來並且存放在目錄`build`中。

在這個範例中，由於資料夾`build`專門存放建置時產生出來的檔案，所以這個資料夾也可以稱為`Binary tree`。會需要這種資料夾，可以避免建置的過程中產生過多中間檔，把整個專案搞得很亂。

##### 使用`make`建置
在編輯完`makefile`以後，就來說明如何透過`make`這個工具來建置專案。

我們先從下這個指令來建置專案`example01`:
```sh
make all
```
執行完指令以後，會發現專案中多了一個目錄`build`，而且在該目錄底下會有建置過程中產生的中間檔案，以及最終目標檔`myPow`。
![example01_make_all](./images/example_01_make_all.png)

其實我們也可以直接使用下面這個指令來編譯:
```sh
make
```
這個指令也同樣可以建置專案，而且執行結果與使用`make all`相同，因為`all`這個標籤在`make`中是一個特殊的標籤，它代表了預設編譯的動作。
![example01_make](./images/exmaple_01_make.png)

現在我們來使用這個指令來清除目錄`build`中所有的檔案:
```sh
make clean
```
使用完這個指令以後，目錄`build`所有的檔案都會不清除掉。有時前幾次建置的中間檔可能有問題，就可以先用`make clean`把編譯出來的所有檔案都先清掉，這樣就可以重新再編譯一次。
![example01_make_clean](./images/example_01_make_clean.png)

其實還有一種情況也會使用到`make clean`，那就是在專案中的程式碼沒更動到的情況下，而且已經編譯過了，可是想再編譯一次並且追加一些編譯參數。在`gcc`這個指令中，可以加上參數`-O3`，這個時候編譯的過程中編譯器會最佳化編譯出來的檔案，使編譯出來的程式檔案更小且跑起來更快一些。假設我們的專案中有幾個bug需要修正，但我們還不知道那些bug在哪裡，這個時候就應該使用`gdb`這類的工具debug。如果要使用`gdb`，就必須再編譯時加上一個參數`-g`才行，編譯出來的檔案才會有額外的資訊方便debug。

前面說明`makefile`的時候有提到可以宣告變數，在我們使用`make`這個工具時，就可以用上這些變數在編譯時做些特別的事。剛剛我們建置的時候沒有額外加編譯參數，現在我們可以試試看加上`-g`這個參數來編譯看看。前面也有提到，在範例`example01`的`makefile`中有宣告變數`CFLAGS`，這個變數用來給予編譯參數，所以我們可以在使用`make`這個指令的同時搭配`CFLAGS`給予編譯參數。
```sh
make clean
make CFLAGS+=-g
```
等編譯完成，可執行檔`myPow`會因為包含一些除錯用的資訊，檔案可能會比較大，但是我們也可以使用`gdb`除錯。
![example01_make_debug](./images/example01_make_debug.png)

### 使用cmake建置
前面介紹了怎麼使用`make`建置一個專案，不管專案中有多大，只要`makefile`的編譯規則寫好，都能很輕易建置專案，而且在建置的過程中只會對有更新過的檔案編譯，所以可以節省很多時間。有這麼好用的工具可以使用，為什麼還要使用`cmake`呢？那是因為`make`這個工具沒有跨平台。一般來說`make`在Unix-like的作業系統中才能使用，像是Linux。假如想在Windows中使用`make`，要嘛使用WSL要嘛使用msys2，使用上會比較麻煩。

`cmake`的優勢在於支援跨平台。假設我們在開發一個用專案，在這個專案中沒有使用到只支援特定作業系統的函式庫，像是使用到Linux的`fork()`，那麼就可以在Linux和Windows上建置這個專案。雖說`cmake`的確是一個用於建置專案的工具，但是使用上又跟`make`有點不同。當我們為一個專案編輯好`CMakeLists.txt`以後，透過`cmake`建置該專案的流程如下:
1. 先在該專案中建立一個用於建置的資料夾
2. 使用`cmake`產生建置工具所需的設定檔
3. 透過`cmake`所產生的檔案，使用建置工具來編譯專案中的原始碼
從上面的流程可以知道，`cmake`不會直接建置專案，而是先產生建置工具所需的設定檔，然後使用那些設定檔透過建置工具來編譯專案。`cmake`不直接編譯專案的程式碼，而是先產生建置工具所需的設定檔，主要是因為這樣可以支援多種建置工具來編譯專案。在Linux中`cmake`就產生`makefile`，然後使用`make`來編譯專案。在Windows上，`cmake`就產生提供給`Visual Studio`所需的檔案，讓`Visual Studio`來編譯專案。在Mac OS上，`cmake`就產生`xcode`所需的檔案，讓`xcode`來編譯專案。這樣就能達成跨平台的支援。

#### example_02
接下來用範例來簡單說明怎麼使用`cmake`。這裡直接拿`example01`改來用，請先把前一個範例`example01`複製一份，並且命名為`example_02`。因為我們接下來要使用`cmake`建置專案，所以請先把`makefile`刪除掉，然後新增檔案`CMakeLists.txt`，該檔案的內容如下：
```cmake
cmake_minimum_required(VERSION 3.0)

project(example02)

include_directories(src)

add_executable(myPow src/main.c src/calcPow.c)
```
就只是把專案`example_02`編譯成可執行檔`myPow`，假如不把空行算進去，只需要短短的4行就能做完。現在來說明每一行的意義:
* `cmake_minimum_required()`: 這行的用意是指定能使用的`cmake`最低版本。其實沒這行也可以使用，只是如果`CMakeLists.txt`有用到的指令只有在比較舊的版本才能使用，少這一行可能無法建置。
* `project()`: 這行是用來指定專案的名稱，雖然不使用不會怎麼樣，但建議使用會比較好。
* `include_directories()`: 因為標頭檔`calcPow.h`放在目錄`src`中，所以才需要這一行，告訴`cmake`這個專案的`.c`檔中所使用的標頭檔放置的路徑在哪裡。
* `add_executable()`: 這一行是關鍵，它會把在目錄`src`中的`main.c`與`calcPow.c`編譯成可執行檔`myPow`。

現在來說明怎麼使用`cmake`建置，可以先把目錄`build`中的檔案都刪掉。開啟終端機，然後使用移動到`build`中，接著使用下面的指令:
```sh
cmake ..
```
`cmake`這個指令後面必須給予一個參數，用來指定`CMakeLists.txt`所在位置，由於當前目錄在`build`中，而`CMakeLists.tx`在上一層的目錄中，所以`cmake`後面接的參數是`..`。執行結果如下圖所示。
![example_02_cmake](./images/example_02_cmake.png)

到這邊還只是第一步，`cmake`才剛產生出`makefile`。現在使用下面的指令，透過`make`來編譯專案:
```sh
make
```
如下圖所示為執行的過程，由`cmake`產生的`makefile`非常貼心，編譯的過程中還會顯示處理的進度。
![example_02_make](./images/example_02_make.png)
