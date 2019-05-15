CC=gcc
CFLAGS=-std=c++11.

make: firmgen.cpp
    $(CC) -o firmgen