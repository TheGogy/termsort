CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=gnu99 -lncursesw
SRCS = main.c renderer.c arrayutils.c sorting.c
OBJS = $(SRCS:.c=.o)
INSTALL_DIR = $(HOME)/.local/bin
EXEC = termsort

.PHONY: all clean install uninstall

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

install: $(EXEC)
	cp $(EXEC) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(EXEC)
