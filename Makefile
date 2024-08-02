CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = spchk.c
OBJS = $(SRCS:.c=.o)
TARGET = spchk

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)