# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test

# Output executable name
TARGET = $(TEST_DIR)/main

# Source files
SRCS = $(SRC_DIR)/circular_buffer.c $(SRC_DIR)/communication.c $(TEST_DIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler flags
CFLAGS = -I$(INCLUDE_DIR) -Wall -pthread

# Build target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
