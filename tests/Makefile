CC := gcc
CFLAGS := -std=c99 -Wall -Wextra
LDFLAGS := -lcheck -lm -lsubunit

BUILD_DIR := build

SOURCES := $(wildcard *.c)

UNITY_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/unity/%.o, $(SOURCES))
PRECOMP_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/precomp/%.o, $(SOURCES))

UNITY_TARGET := $(BUILD_DIR)/unity_cserio_testing
PRECOMP_TARGET := $(BUILD_DIR)/precomp_cserio_testing

all: $(UNITY_TARGET) $(PRECOMP_TARGET)

$(UNITY_TARGET) : $(UNITY_OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(PRECOMP_TARGET) : $(PRECOMP_OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DCSERIO_IMPLEMENTATION -x c -c ../cserio.h
	$(CC) $(CFLAGS) $^ cserio.o -o $@ $(LDFLAGS)

$(BUILD_DIR)/unity/%.o : %.c  | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DUNITY_TEST -c $< -o $@

$(BUILD_DIR)/precomp/%.o : %.c  | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)/unity/
	mkdir -p $(BUILD_DIR)/precomp/

run:
	./$(UNITY_TARGET)
	./$(PRECOMP_TARGET)

clean:
	rm cserio.o
	rm -r $(BUILD_DIR)

.PHONY: all run clean

