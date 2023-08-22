SRC_DIR := ./src
BIN_DIR := ./build

.PHONY: all clean

all:
	mkdir -p $(BIN_DIR)
	gcc -g $(SRC_DIR)/main.c $(SRC_DIR)/calcPow.c -I$(SRC_DIR) -o $(BIN_DIR)/calcPow

clean:
	rm -rf $(BIN_DIR)/*
