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

### example01
接下來用範例來簡單說明怎麼使用`make`來建置一個專案。這邊建議是照著下面的流程玩過一遍會比較好，假如懶得做一遍，可以直接用[example01](./example01/README.md)。

請先建一個資料夾，該資料夾的名稱可以任意使用，這邊就用`example01`來命名，後面說明比較能統一。在資料夾`example01`中再建一個資料夾，請將該資料夾命名為`src`。資料夾`src`用來放所有的source code，這包含`.c`、`.cpp`、`.h`和`.hpp`這些檔案。也因為資料夾`src`主要用來放source code，所以這個資料夾也可以稱為`Source Tree`。

#### 新增標頭檔`calcPow.h`
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

#### 新增檔案`calcPow.c`
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

#### 新增`main.c`
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

#### 新增`makefile`
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
