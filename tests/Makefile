CC = gcc
CFLAGS = -std=c99 -Wall

SRC_FILES = $(wildcard *.c)

UNITY_TARGET = unity_test_base
PRECOMP_TARGET = precomp_test_base

all: $(UNITY_TARGET) $(PRECOMP_TARGET)

$(UNITY_TARGET):
	$(CC) -DUNITY_TEST main.c -o $@

$(PRECOMP_TARGET):
	$(CC) -DSER_TESTING -DCSERIO_IMPLEMENTATION  -x c -c ../cserio.h
	$(CC) $(SRC_FILES) cserio.o -o $@

run:
	./$(UNITY_TARGET)
	./$(PRECOMP_TARGET)

clean:
	rm -v cserio.o
	rm -v $(UNITY_TARGET) $(PRECOMP_TARGET)

.PHONY: all run clean

