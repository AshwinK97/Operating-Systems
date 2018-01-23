# Conceptual Questions

## 1. What are benefits of C, where is it used

C language is a middle level language, meaning that it can be used for hardware level applications and software applications. C is also a very readable language considering how low level it actually is. C was used to make the Linux operating system as well as most driver software for modern computers. C is also used for most embedded software such as micro controller firmware.

## 2. What is a compiler, what does it do?

The compiler is program that takes code written in a spcific syntax and converts it to machcine code which can be executed by a specific processor. Compilers are language and architecture specific. This means that there will be a different C compiler for each type of architecture. The compiler will parse through the code checking for syntax errors. It will then tokenize the code into individual parts. Then, the compiler will attempt to derive the symmantics of these parts and it will attempt to optimize the code for the specific architecture. Then, the required libraries as well as other required files will be bundled and converted to machine code as an executable.

## 3. What is a Makefile, what does it do?

A make file is a simple way to associate short names called targets to a set of scripts, usually used to call compilation commands when building software. In order to use makefiles, the Makefile program must be installed. While in the containing directory, the user simply types 'make' and the makefile will go through its commands and compile the required files. This is a fast way to build software so that other users can quickly build and test it without compiling each individual file.

## 4. Name 5 header files from C library, explain their purpose

### stdlib.h

General utilities for writinng c programs including memory management, program utilities, string conversions and random values.

### stdio.h

Input and output utilities for reading and writing to files and command line.

### string.h

String utilities including case changing, comparing and copying of strings.

### time.h

Clock utilities for timing events and processes, calculating time and formatting based on common time formats.

### signal.h

Provides utilities to handle signals.

## 5. Look up one of the functions from each header and describe what it does

### stdlib.h - void* malloc(size_t size)

Allocates memory based on amount specified by 'size'.

### stdio.h - int printf(const char \*format, ...)

Writes string to stdout based on string template by replacing arguments.

### string.h - char \*strcpy(char \*dest, const char \*src)

Copies a null terminated string pointed to by src to the destination pointed to by dest.

### time.h - double difftime(time_t time_end, time_t time_beg)

Computes the difference between two calender times as time_t objects in seconds.

### signal.h - void abort(void)

Causes abnormal program termination unless SIGABRT is caught and handeled by a different signal handeler.

# Application Questions

## 1. 