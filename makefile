CC = gcc
CFLAGS = -Wall

SRCDIR = src
BUILDDIR = build

SRC = $(SRCDIR)/main.c
TARGET = $(BUILDDIR)/mineCweeper

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
