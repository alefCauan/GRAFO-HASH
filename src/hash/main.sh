#!/bin/sh

SRC_MAIN="main.c"
SRC_HASH="hash.c"
OUT="out"


gcc -g -o $OUT $SRC_HASH $SRC_MAIN 
# valgrind --leak-check=full 
./$OUT