CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk4)
LDFLAGS = $(shell pkg-config --libs gtk4)

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ASSET_DIR = asset

EXECUTABLE = $(BUILD_DIR)/main

SOURCES = $(shell find $(SRC_DIR) -name "*.c")

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) main.c $(SOURCES) -o $(EXECUTABLE) $(CFLAGS) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)
