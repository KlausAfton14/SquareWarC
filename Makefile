CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL2 -lm

SRC = main.c
BIN = bin/gierka

all: format build run

format:
	clang-format -i $(SRC)

build:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

run:
	./$(BIN)

clean:
	rm -rf bin