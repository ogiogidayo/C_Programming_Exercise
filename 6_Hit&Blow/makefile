CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm
SRCS = main.c number.c hitblow.c
OBJS = $(SRCS:.c=.o)
BIN = main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) core