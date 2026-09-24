CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
PICFLAGS = -fPIC

STATIC_LIB = lib/libmyutils.a
DYNAMIC_LIB = lib/libmyutils.so

STATIC_TARGET = bin/client_static
DYNAMIC_TARGET = bin/client_dynamic

STATIC_OBJECTS = obj/mystrfunctions_static.o obj/myfilefunctions_static.o
PIC_OBJECTS = obj/mystrfunctions_pic.o obj/myfilefunctions_pic.o
MAIN_OBJECT = obj/main.o

.PHONY: all build static dynamic clean

all: build

build: static dynamic

static: $(STATIC_TARGET)

dynamic: $(DYNAMIC_TARGET)

# -------------------------
# Static Library
# -------------------------

$(STATIC_LIB): $(STATIC_OBJECTS)
	ar rcs $(STATIC_LIB) $(STATIC_OBJECTS)

obj/mystrfunctions_static.o: src/mystrfunctions.c
	$(CC) $(CFLAGS) -c src/mystrfunctions.c -o obj/mystrfunctions_static.o

obj/myfilefunctions_static.o: src/myfilefunctions.c
	$(CC) $(CFLAGS) -c src/myfilefunctions.c -o obj/myfilefunctions_static.o

$(STATIC_TARGET): $(MAIN_OBJECT) $(STATIC_LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -Llib -lmyutils -o $(STATIC_TARGET)

# -------------------------
# Dynamic Library
# -------------------------

$(DYNAMIC_LIB): $(PIC_OBJECTS)
	$(CC) -shared -o $(DYNAMIC_LIB) $(PIC_OBJECTS)

obj/mystrfunctions_pic.o: src/mystrfunctions.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/mystrfunctions.c -o obj/mystrfunctions_pic.o

obj/myfilefunctions_pic.o: src/myfilefunctions.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/myfilefunctions.c -o obj/myfilefunctions_pic.o

$(DYNAMIC_TARGET): $(MAIN_OBJECT) $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -Llib -lmyutils -o $(DYNAMIC_TARGET)

# -------------------------
# Main Object
# -------------------------

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

# -------------------------
# Clean
# -------------------------

clean:
	rm -f obj/*.o
	rm -f $(STATIC_LIB)
	rm -f $(DYNAMIC_LIB)
	rm -f $(STATIC_TARGET)
	rm -f $(DYNAMIC_TARGET)
