#include "short_path.h"

int main() 
{
    int n, n_edges, origin, dest;

    do {
        printf("Digite o número de vértices: ");
        scanf("%d", &n);
    } 
    while (n <= 0 || n > MAX_VERT);
    
    Graph *graph = create_graph(n);

    do {
        printf("Digite o número de arestas: ");
        scanf("%d", &n_edges);
    } 
    while (n_edges < 0);
    


    rand_edges(graph, n_edges);
    // printf("Arestas geradas automaticamente:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < graph->degree[i]; j++) {
    //         printf("(%d -> %d) com confiabilidade %.2f\n", i, graph->adj[i][j].dest, graph->adj[i][j].rely);
    //     }
    // }

    do {
        printf("Digite o vértice de origem (0 a %d): ", n - 1);
        scanf("%d", &origin);
    } 
    while (origin < 0 || origin >= n);

    do {
        printf("Digite o vértice de destino (0 a %d): ", n - 1);
        scanf("%d", &dest);
    } 
    while (dest < 0 || dest >= n);

    most_reliable_way(graph, origin, dest);

    for (int i = 0; i < n; i++) 
        free(graph->adj[i]);
    
    free(graph->adj);
    free(graph->degree);
    free(graph);

    return 0;
}