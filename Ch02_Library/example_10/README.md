# Example_10
這個範例主要展示如何將一個專案安裝到電腦中。假如這個專案本身是一個函式庫，其他專案也可以很輕易使用到該函式庫。

這邊主要會示範怎麼使用幾個重要的指令:
* `configure_file()`: 使用給定的樣板產生特定內容的檔案
* `install()`: 專門用來處理安裝檔案
* `add_custom_target()`和`add_custom_command()`: 這兩個指令搭配使用，實現`make uninstall`這個指令

