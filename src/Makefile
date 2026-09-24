CC = gcc

CFLAGS = -Wall -Wextra -I../include

TARGET = ../bin/client

SOURCES = main.c mystrfunctions.c myfilefunctions.c

OBJECTS = main.o mystrfunctions.o myfilefunctions.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

mystrfunctions.o: mystrfunctions.c
	$(CC) $(CFLAGS) -c mystrfunctions.c -o mystrfunctions.o

myfilefunctions.o: myfilefunctions.c
	$(CC) $(CFLAGS) -c myfilefunctions.c -o myfilefunctions.o

clean:
	rm -f $(OBJECTS)
