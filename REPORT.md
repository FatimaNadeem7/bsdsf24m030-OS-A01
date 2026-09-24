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
      # Feature 4: Creating and Using Dynamic Library 

## 1. Position-Independent Code (-fPIC)

Position-Independent Code (PIC) is code that can run correctly regardless of where it is loaded into memory.   

The `-fPIC` option tells GCC to generate position-independent code.

It is important for shared libraries because a dynamic library can be loaded at different memory addresses by different programs. The code must therefore be able to work correctly without depending on a fixed memory address.

In this project, `-fPIC` was used when compiling the object files for `libmyutils.so`.

## 2. Difference Between Static and Dynamic Client File Sizes

The static client `client_static` and dynamic client `client_dynamic` have different file sizes.

The static executable is generally larger because the required code from `libmyutils.a` is copied into the executable during linking.

The dynamic executable is generally smaller because the code from `libmyutils.so` remains in the shared library instead of being copied into the executable.

When `client_dynamic` runs, the operating system's dynamic loader loads the required shared library separately.

Therefore, the difference in size occurs because static linking includes library code inside the executable, while dynamic linking keeps the library code in a separate `.so` file.

## 3. LD_LIBRARY_PATH

`LD_LIBRARY_PATH` is an environment variable that tells the Linux dynamic loader which directories to search for shared libraries.

When `./bin/client_dynamic` was first executed, the loader could not find `libmyutils.so` because the project's `lib/` directory was not one of its default library search locations.

The error was:

`cannot open shared object file: No such file or directory`

We fixed this by using:

`export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH`

After setting this variable, the loader was able to find `libmyutils.so` in the project's `lib/` directory and the program executed successfully.

This shows that the dynamic loader is responsible for finding and loading shared libraries when a dynamically linked program starts. The library must be located in a directory known to the loader.
