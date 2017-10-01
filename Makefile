CFLAGS = -Wall

all: cdecl

cdecl: main.c
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g
debug: cdecl

.PHONY: clean
clean:
	-rm -f cdecl
