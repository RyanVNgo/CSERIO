CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = -lcheck -lm -lsubunit

UNITY_TARGET = unity_cserio_testing
PRECOMP_TARGET = precomp_cserio_testing

all: $(UNITY_TARGET) $(PRECOMP_TARGET)

$(UNITY_TARGET):
	$(CC) $(CFLAGS) -DUNITY_TEST main.c $(LDFLAGS) -o $@

$(PRECOMP_TARGET):
	$(CC) $(CFLAGS) -DCSERIO_IMPLEMENTATION -x c -c ../cserio.h
	$(CC) $(CFLAGS) main.c cserio.o $(LDFLAGS) -o $@

run:
	./$(UNITY_TARGET)
#	./$(PRECOMP_TARGET)

clean:
	rm -v cserio.o
	rm -v $(UNITY_TARGET) $(PRECOMP_TARGET)

.PHONY: all run clean

