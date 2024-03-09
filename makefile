CC = gcc
SOURCES = main.o
CFLAGS=-Wall -Wextra -Werror -D_DEFAULT_SOURCE -std=c99
all: fd_table
fd_table: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: help
help:
	@echo "  all            setting up program"
	@echo "  clean          Remove object files"

clean:
	rm -f *.o fd_table