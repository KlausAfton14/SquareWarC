SRC = $(wildcard src/*.c)
BIN_DIR = bin

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lSDL2 -lm

BIN = $(BIN_DIR)/gierka

WIN_CC = x86_64-w64-mingw32-gcc
WIN_CFLAGS = -Wall -Wextra -std=c99 -Iinclude \
             -I/usr/x86_64-w64-mingw32/include
WIN_LDFLAGS = -L/usr/x86_64-w64-mingw32/lib \
              -lSDL2 -lm

WIN_BIN = $(BIN_DIR)/SquareWar.exe

all: format build run

format:
	clang-format -i $(SRC)

build:
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

win:
	mkdir -p $(BIN_DIR)
	$(WIN_CC) $(WIN_CFLAGS) $(SRC) -o $(WIN_BIN) $(WIN_LDFLAGS)

run:
	./$(BIN)

clean:
	rm -rf $(BIN_DIR)
