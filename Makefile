CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ASSET_DIR = asset

EXECUTABLE = $(BUILD_DIR)/main

SOURCES = $(shell find $(SRC_DIR) -name "*.c")

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) main.c $(SOURCES) -o $(EXECUTABLE) $(CFLAGS) $(LDFLAGS) && ./$(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)
