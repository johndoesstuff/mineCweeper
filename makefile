CC = gcc
CFLAGS = -Wall

SRCDIR = src
BUILDDIR = build

SRC = $(SRCDIR)/main.c
OBJ = $(SRC:.c=.o)
TARGET = $(BUILDDIR)/mineCweeper

LDFLAGS = -lncurses

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
