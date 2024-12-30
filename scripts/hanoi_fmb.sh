#!/bin/sh

SRC_MAIN="../src/hanoi_FMB/main.c"
SRC_HANOI="../src/hanoi_FMB/hanoi_FMB.c"
OUT="hanoi_FMB"

gcc -g -o ../bin/$OUT $SRC_HANOI $SRC_MAIN

../bin/$OUT