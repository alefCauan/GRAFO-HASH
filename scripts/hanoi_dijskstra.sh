#!/bin/sh

SRC_MAIN="../src/hanoi_dijskstra/main.c"
SRC_HANOI="../src/hanoi_dijskstra/hanoi_dijskstra.c"
OUT="hanoi_dijskstra"

gcc -g -o ../bin/$OUT $SRC_HANOI $SRC_MAIN

../bin/$OUT