#ifndef HANOI_FMB_H
#define HANOI_FMB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_STATES 256  // 4^3 possíveis estados
#define NUM_DISKS 4
#define NUM_PINS 3

typedef struct {
    int states[NUM_DISKS];
} Graph;

bool is_valid_move(Graph vet1, Graph vet2);
void matrix_gen(Graph *graph, int matrix[][MAX_STATES]);
void ford_moore_bellman(int start, int end, int *prev, int *distance, int mat_adj[][MAX_STATES]);
void show_path(int start, int end, int *prev, int *distance);
void show_graph(Graph *graph);
void timers();

#endif