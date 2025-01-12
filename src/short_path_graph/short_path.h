#ifndef SHORT_PATH_H
#define SHORT_PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>


#define MAX_VERT 100  
#define INF -DBL_MAX      // Representação de Confiabilidade mínima (-∞)


typedef struct {
    int dest;
    double rely;
} Edge;

typedef struct {
    int vert_num;
    int *degree; // Quantidade de vizinhos por vértice
    Edge **adj; // Lista de adjacências
} Graph;

Graph *create_graph(int vert_num);

// Função para adicionar uma aresta ao grafo
void add_edge(Graph *graph, int origin, int dest, double rely);

// Função para encontrar o caminho mais confiável usando um algoritmo baseado em Dijkstra
void most_reliable_way(Graph *graph, int origin, int dest);

void rand_edges(Graph *graph, int n_edges);

#endif