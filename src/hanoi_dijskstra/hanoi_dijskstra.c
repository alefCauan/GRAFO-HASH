
#include "hanoi_dijskstra.h"

bool is_valid_move(Graph vet1, Graph vet2)
{
    
    bool valid = true;

    int variation = 0, dif_ind = -1;

    for (int i = 0; i < NUM_DISKS && variation <= 1; ++i)
    {
        if (vet1.states[i] != vet2.states[i])
        {
            variation++;
            dif_ind = i;
        }
    }

    if (variation > 1)
        valid = false;
    else
    {
        int invalid = 1;
        for (int i = 0; i < NUM_PINS && invalid; i++)
        {
            if (i != dif_ind && ((vet1.states[i] == vet1.states[dif_ind] && i < dif_ind) ||
                (vet2.states[i] == vet2.states[dif_ind] && i < dif_ind)))
                invalid = 0;
        }

        if (!invalid)
            valid = false;
    }

    return (valid);
}

void matrix_gen(Graph *graph, int mat_adj[][MAX_STATES])
{
    for (int i = 0; i < MAX_STATES; i++)
        for (int j = 0; j < MAX_STATES; j++)
            mat_adj[i][j] = 0;

    int num;

    for (int i = 0; i < MAX_STATES; i++)
    {
        num = i;
        for (int disk = 0; disk < NUM_DISKS; disk++)
        {
            graph[i].states[disk] = num % NUM_PINS + 1;
            num /= NUM_PINS;
        }
    }

    for (int x = 0; x < MAX_STATES; x++) 
    {
        for (int y = 0; y < MAX_STATES; y++)
            if (is_valid_move(graph[x], graph[y]))
                mat_adj[x][y] = 1;
            else
                mat_adj[x][y] = 0;
    }
}

void dijskstra(int start, int *prev, int *distance, int mat_adj[][MAX_STATES])
{
    int wandered[MAX_STATES], curr = 0;

    for(int states = 0; states   < MAX_STATES; states++)
    {
        prev[states]      = -1;
        distance[states]  = INT_MAX;
        wandered[states]  =  0;
    }

    distance[start] = 0;

    while(curr < MAX_STATES)
    {
        int small_vet = -1;

        for (int i = 0; i < MAX_STATES - 1; i++)
            if (!wandered[i] && (small_vet == -1 || distance[i] < distance[small_vet]))
                small_vet = i;

        if(!(small_vet == -1 || distance[small_vet] == INT_MAX))
        {
            wandered[small_vet] = 1;

            for (int v = 0; v < MAX_STATES; v++)
            {
                if (!wandered[v] && mat_adj[small_vet][v] && distance[small_vet] != -1 && 
                distance[small_vet] + mat_adj[small_vet][v] < distance[v])
                {
                    distance[v] = distance[small_vet] + mat_adj[small_vet][v];
                    prev[v] = small_vet; 
                }
            }
        }

        curr ++;
    }
}

void show_path(int start, int end, int *prev, int *distance)
{
    if (distance[end] == INT_MAX)
        printf("Não há caminho acessível de %d para %d.\n", start, end);
    else
    {
        printf("Menor caminho de %d para %d: %d\n", start, end, distance[end]);

        int path[MAX_STATES], ind = 0, curr = end;

        while (curr != -1)
        {
            path[ind++] = curr;  
            curr = prev[curr];  
        }
        for (int i = ind - 1; i >= 0; i--)
        {
            printf("%d", path[i]);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");
    }
}

void show_graph(Graph *graph)
{
    for (int i = 0; i < MAX_STATES; ++i)
    {
        printf("vertex %d: ", i);
        for (int j = 0; j < NUM_DISKS; j++)
            printf("%d ", graph[i].states[j]);
        printf("\n");
    }
}

void timers()
{
    Graph graph[MAX_STATES];
    int mat_adj[MAX_STATES][MAX_STATES];

    matrix_gen(graph, mat_adj);
    show_graph(graph);

    int begin, finish;
    printf("Digite o índice da configuração inciar (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &begin);
    printf("Digite o índice da configuração finalizar (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &finish);

    int distances[MAX_STATES];
    int prev[MAX_STATES];

    clock_t start, end;
    start = clock();
    dijskstra(begin, prev, distances, mat_adj);
    end = clock();

    show_path(begin, finish, prev, distances);

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo do algoritmo de dijkshtra: %f segundos\n", tempo);
}