CC = gcc

INCDIR = ../src
LIBDIR = ../src

CFLAGS = -std=c99 -I$(INCDIR)
LDFLAGS = -L$(LIBDIR) -lcserio

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

TARGET = test-runner

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
