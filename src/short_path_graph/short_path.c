#include "short_path.h"

Graph *create_graph(int vert_num) 
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vert_num = vert_num;
    graph->degree = (int *)calloc(vert_num, sizeof(int));
    graph->adj = (Edge **)malloc(vert_num * sizeof(Edge *));

    for (int i = 0; i < vert_num; i++) 
        graph->adj[i] = NULL;

    return graph;
}

// Função para adicionar uma aresta ao grafo
void add_edge(Graph *graph, int origin, int dest, double rely) 
{
    graph->degree[origin]++;
    graph->adj[origin] = (Edge *)realloc(graph->adj[origin], graph->degree[origin] * sizeof(Edge));
    graph->adj[origin][graph->degree[origin] - 1].dest = dest;
    graph->adj[origin][graph->degree[origin] - 1].rely = rely;
}

// Função para encontrar o caminho mais confiável usando um algoritmo baseado em Dijkstra
void most_reliable_way(Graph *graph, int origin, int dest) 
{
    int n = graph->vert_num;
    double max_prob[MAX_VERT];  
    int ant[MAX_VERT]; 
    int visited[MAX_VERT] = {0}; 

    for (int i = 0; i < n; i++) 
    {
        max_prob[i] = INF;
        ant[i] = -1;
    }

    max_prob[origin] = 0; 

    for (int i = 0; i < n; i++) 
    {
        // Encontrar o vértice com a maior confiabilidade acumulada que ainda não foi visited
        int u = -1;
        for (int j = 0; j < n; j++) 
        {
            if (!visited[j] && (u == -1 || max_prob[j] > max_prob[u])) 
                u = j;
        }

        if (u == -1 || max_prob[u] == INF) break; // Sem mais vértices alcançáveis
        visited[u] = 1;

        // Atualizar as confiabilidades dos vizinhos
        for (int j = 0; j < graph->degree[u]; j++) 
        {
            int v = graph->adj[u][j].dest;
            double rely = graph->adj[u][j].rely;
            double new_prob = max_prob[u] + log(rely);
            
            if (new_prob > max_prob[v]) 
            {
                max_prob[v] = new_prob;
                ant[v] = u;
            }
        }
    }

    // Reconstruir o caminho mais confiável
    if (max_prob[dest] > INF)
    {
        double rely = exp(max_prob[dest]);

        printf("Confiabilidade máxima: %.6f\n", rely);
        printf("Caminho mais confiável: ");

        int caminho[MAX_VERT], tam = 0, v = dest;
        while (v != -1) 
        {
            caminho[tam++] = v;
            v = ant[v];
        }
        
        for (int i = tam - 1; i >= 0; i--) 
            printf("%d%s", caminho[i], (i == 0) ? "\n" : " -> ");

    } 
    else 
        printf("Não existe caminho entre %d e %d.\n", origin, dest);
}


void rand_edges(Graph *graph, int n_edges) 
{
    srand(time(NULL));
    for (int i = 0; i < n_edges; i++) 
    {
        int origin = rand() % graph->vert_num;
        int dest = rand() % graph->vert_num;
        while (dest == origin) 
            dest = rand() % graph->vert_num;
        
        double rely = (rand() % 101) / 100.0; // Valor entre 0.0 e 1.0
        add_edge(graph, origin, dest, rely);
    }
}

