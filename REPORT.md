# Feature 3: Creating and Using Static Library

## 1. Comparison of Makefiles

In Part 2, the Makefile compiled the source files into object files and then directly linked all the object files to create the executable.

In Part 3, the Makefile was modified to first create a static library called `libmyutils.a`. The utility object files `mystrfunctions.o` and `myfilefunctions.o` are placed inside this library.

The important differences are:

- Part 2 directly links all object files.
- Part 3 creates a static library using `ar`.
- Part 3 uses `LIB = lib/libmyutils.a`.
- The final executable is linked using `-Llib -lmyutils`.
- The final executable is named `client_static`.

Therefore, Part 3 separates the utility functions into a reusable static library.

## 2. Purpose of the ar Command

The `ar` command is used to create and modify archive files.

In this project, `ar` combines the object files into the static library:

`lib/libmyutils.a`

The command used was:

`ar rcs lib/libmyutils.a obj/mystrfunctions.o obj/myfilefunctions.o`

The options mean:

- `r` — insert or replace files in the archive.
- `c` — create the archive if it does not exist.
- `s` — create or update the symbol index.

`ranlib` is often used after `ar` to create or update the symbol index of a static library. This index helps the linker quickly find the required symbols. When the `s` option is used with `ar`, the symbol index is created automatically, so a separate `ranlib` command is not necessary.

## 3. nm and Static Linking

When `nm` is run on the `client_static` executable, symbols for functions such as `mystrlen` are present.

For example:

`nm bin/client_static | grep mystrlen`

shows the `mystrlen` symbol in the executable.

This demonstrates that the required function code from the static library has been included in the final executable during static linking.

In static linking, the linker takes the required object code from the `.a` library and places it into the executable. Therefore, functions such as `mystrlen` become part of `client_static`.
