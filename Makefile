CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/client

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
	rm -f $(TARGET)
