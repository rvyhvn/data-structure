# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g  # Added the -g flag for debugging

# Directories
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

# Source and header files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
HEADER_FILES = $(wildcard $(LIB_DIR)/*.h)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target executable
TARGET = main

# Default target
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

.PHONY: all clean debug
