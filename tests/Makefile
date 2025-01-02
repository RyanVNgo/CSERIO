CC = gcc
CFLAGS = -std=c99 -Wall -Iinclude
LDFLAGS = -Llib -lcserio

SRC_FILES = $(wildcard *.c)

OBJ_DIR	= obj
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = cserio_test

all: $(TARGET)

$(TARGET) : $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_FILES) : $(SRC_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_FILES) -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -v -f $(OBJ_FILES)
	rm -v -d -f $(OBJ_DIR)
	rm -v -f $(TARGET)

.PHONY: all run clean
