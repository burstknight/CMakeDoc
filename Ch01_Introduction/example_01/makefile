SRC_DIR := ./src
BIN_DIR := ./build
TARGET := myExe

CFLAGS := 
CC := gcc

.PHONY: all clean

all: $(BIN_DIR)/myMathLib.o
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(BIN_DIR)/myMathLib.o -o $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/myMathLib.o:
	mkdir -p $(BIN_DIR)
	$(CC) -c $(CFLAGS) $(SRC_DIR)/myMathLib.c -I$(SRC_DIR) -o $@

clean:
	rm -rf $(BIN_DIR)/*
