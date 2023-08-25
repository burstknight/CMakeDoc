# Example01
這個範例用來說明如何使用`make`這個指令來建置一個專案。

由於`make`是Linux上的指令，假如想在Windows上想玩玩看這個範例，可以安裝`WSL`或`msys2`。這個範例只是簡單介紹怎麼使用`make`，所以就不另外說明怎麼在`WSL`和`msys2`安裝過程。假如真的想使用`msys2`，可以參考我的另一個[repo](https://github.com/burstknight/msys2_setup)，在這個repo中提供一個shell腳本檔，裡面有撰寫一些指令，可以自動化安裝好必要的套件。

## 建置專案
如果想嘗試建置專案，可以使用下面的指令:
```sh
make all
```
除此之外，下面的指令執行過程也與上面的相同。:
```sh
make
```

假如想用`gdb`這個工具除錯，可以使用下面的指令追加編譯參數`-g`:
```sh
make CFLAGS+=-g
```

如果想清除先前建置產生的檔案，可以使用下面的指令:
```sh
make clean
```

