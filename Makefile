# Compiler and flags
CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = -liniparser

# Directories
SRC_DIR = src
OBJ_DIR = build
OUT_DIR = bin
INSTALL_BIN_DIR = /usr/bin

# Target binary
TARGET_NAME = aws-rat-picker
TARGET = $(OUT_DIR)/$(TARGET_NAME)

# Source and object files
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link final binary
$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .c to .o, preserving folder structure
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: all
	./$(TARGET)

# Install
install: $(TARGET)
	install -Dm755 $(TARGET) $(INSTALL_BIN_DIR)/$(TARGET_NAME)

# Uninstall
uninstall:
	rm -f $(INSTALL_BIN_DIR)/$(TARGET_NAME)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)
