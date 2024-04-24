
BACKEND ?= ncurses

# Set variables based on the chosen backend
ifeq ($(BACKEND), sdl)
    RENDERER_SRC = renderer_sdl.c
    LIBS = -lSDL2
else ifeq ($(BACKEND), ncurses)
    RENDERER_SRC = renderer_ncurses.c
    LIBS = -lncursesw
else
    $(error Unsupported backend. Please choose either sdl or ncurses.)
endif

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=gnu99 $(LIBS)
SRCS = main.c arrayutils.c sorting.c $(RENDERER_SRC)
OBJS = $(SRCS:.c=.o)
INSTALL_DIR ?= $(HOME)/.local/bin
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
