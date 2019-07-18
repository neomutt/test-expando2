CC	= gcc
RM	= rm -fr

OUT	= main

CFLAGS	+= -Wall
CFLAGS	+= -Wno-unused-parameter
CFLAGS	+= -g
CFLAGS	+= -O0
CFLAGS	+= -fno-omit-frame-pointer

all:	$(OUT)

main: main.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OUT)

