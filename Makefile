CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ASSET_DIR = asset

EXECUTABLE = $(BUILD_DIR)/main

SOURCES = $(shell find $(SRC_DIR) -name "*.c")
CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0) -I$(INCLUDE_DIR) -g -O0
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ASSET_DIR = asset

EXECUTABLE = $(BUILD_DIR)/main

# Find all .c files in SRC_DIR
SOURCES = $(shell find $(SRC_DIR) -name "*.c")
# Create a corresponding .o file for each .c file
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target
all: $(EXECUTABLE)

# Link all object files into the final executable
$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Compile each .c file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)  # Ensure the directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) main.c $(SOURCES) -o $(EXECUTABLE) $(CFLAGS) $(LDFLAGS) && ./$(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)