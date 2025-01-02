CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -Wextra

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

HDR_FILE = cserio.h

BIN_DIR = bin
LIB_DIR = $(BIN_DIR)/lib
INC_DIR = $(BIN_DIR)/include

TEST_DIR = tests

prefix = $(LIB_DIR)

TARGET = libcserio.a

.PHONY: all clean install

# compile 
all: $(TARGET)

$(TARGET) : $(OBJ_FILES) | $(LIB_DIR) $(INC_DIR)
	$(AR) rcs $(LIB_DIR)/$@ $<
	cp $(SRC_DIR)/$(HDR_FILE) $(INC_DIR)/$(HDR_FILE)

$(OBJ_FILES) : $(SRC_FILES) | $(OBJ_DIR)
	gcc -c $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	
$(LIB_DIR) : $(BIN_DIR)
	mkdir -p $(LIB_DIR)

$(INC_DIR) : $(BIN_DIR)
	mkdir -p $(INC_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

# install 
install: $(TARGET)
ifneq ($(prefix), $(LIB_DIR))
	mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/include
	cp -r $(BIN_DIR)/* $(prefix)
endif

# testing 
tests: $(TARGET)
	mkdir -p $(TEST_DIR)/lib
	mkdir -p $(TEST_DIR)/include
	cp -r $(BIN_DIR)/* $(TEST_DIR) 
	$(MAKE) -C $(TEST_DIR)

tests-run: 
	$(MAKE) run -C $(TEST_DIR)

tests-clean: 
	rm -r $(TEST_DIR)/lib
	rm -r $(TEST_DIR)/include
	$(MAKE) clean -C $(TEST_DIR)

# clean 
clean:
	rm -v -f $(OBJ_FILES)
	rm -v -d -f $(OBJ_DIR)
	rm -v -r -f $(BIN_DIR)

