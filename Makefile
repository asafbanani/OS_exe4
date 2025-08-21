CC = gcc
DEBUG = -g
CFLAGS = -Wall -Werror $(DEBUG)

SRC = nicecmp.c loopcmp.c
EXE = nicecmp loopcmp

.PHONY: all clean

all: $(EXE)

digcmp: nicecmp.c
	$(CC) $(CFLAGS) -o $@ $<

lencmp: loopcmp.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE)
