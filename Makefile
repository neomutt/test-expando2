CC	= gcc
RM	= rm -fr

OUT	= main

CFLAGS	+= -Wall
CFLAGS	+= -Wno-unused-parameter
CFLAGS	+= -ggdb3
CFLAGS	+= -O0
CFLAGS	+= -fno-omit-frame-pointer
CFLAGS	+= -Wextra
CFLAGS	+= -Wpedantic
CFLAGS	+= -Wformat-security
CFLAGS	+= -Wshadow
CFLAGS	+= -Wstrict-prototypes
CFLAGS	+= -Wundef
CFLAGS	+= -Wunused-result
CFLAGS	+= -Wimplicit-fallthrough
CFLAGS	+= -Wformat-truncation=2
CFLAGS	+= -Werror

all:	$(OUT)

main: main.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

force:

test:	$(OUT) force
	./$(OUT) "pqr %a %X jkl"

clean:
	$(RM) $(OUT)

