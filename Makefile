CFLAGS = -Wall

all: cdecl doc

cdecl: main.c
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g
debug: cdecl

doc: cdecl.1

cdecl.1: cdecl.pod
	@echo -- Generating manpage from POD:
	pod2man --section=1 --center="cdecl" $? $@

.PHONY: clean
clean:
	-rm -f cdecl
	-rm -f *.1
