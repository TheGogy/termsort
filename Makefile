CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99

SRCS = main.c renderer.c
OBJS = $(SRCS:.c=.o)
EXEC = termsort

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
