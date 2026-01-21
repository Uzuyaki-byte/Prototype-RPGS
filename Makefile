CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
# Default LDFLAGS for Linux
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# --- OS Detection ---
ifeq ($(OS),Windows_NT)
    # Windows-specific overrides
    TARGET_EXTENSION = .exe
    LDFLAGS = -lraylib -lgdi32 -lwinmm
else
    # Linux-specific additions
    TARGET_EXTENSION =
    CFLAGS += -I/usr/local/include
    LDFLAGS += -L/usr/local/lib
endif

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/demo$(TARGET_EXTENSION)

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
