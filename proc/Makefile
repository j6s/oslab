SOURCES = $(wildcard *.c)
PROGS = $(SOURCES:.c=)
all: $(PROGS)

.c:
	gcc -Wall -Werror -o $@ $<

clean: 
	-rm $(PROGS)
