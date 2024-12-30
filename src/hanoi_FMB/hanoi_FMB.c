#include "hanoi_FMB.h"

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

void ford_moore_bellman(int start, int end, int *prev, int *distance, int mat_adj[][MAX_STATES])
{
    for (int i = 0; i < MAX_STATES; i++) 
    {
        prev[i] = -1;
        distance[i] = INT_MAX;
    }

    distance[start] = 0;
    int isUpdated = 1;

    for (int i = 0; i < MAX_STATES - 1 && isUpdated; ++i)
    {
        isUpdated = 0;
        for (int j = 0; j < MAX_STATES; ++j)
        {
            if (distance[j] != INT_MAX)
            {
                for (int k = 0; k < MAX_STATES; k++)
                {
                    if (mat_adj[j][k] != 0 && distance[j] + mat_adj[j][k] < distance[k])
                    {
                        distance[k] = distance[j] + mat_adj[j][k];
                        prev[k] = j;
                        isUpdated = 1;
                    }
                }
            }
        }
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
        for (int j = 0; j < NUM_PINS; j++)
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

    int start, end;
    printf("Digite o índice da configuração Inicial (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &start);
    printf("Digite o índice da configuração Final (0 a %d): ", MAX_STATES - 1);
    scanf("%d", &end);

    int distance[MAX_STATES];
    int prev[MAX_STATES];

    clock_t begin, finish;
    begin = clock();
    ford_moore_bellman(start, end, prev, distance, mat_adj);
    finish = clock();

    show_path(start, end, prev, distance);

    double time = (double)(finish - begin) / CLOCKS_PER_SEC;
    printf("Tempo do algoritmo de Ford-MMoore-Bellman: %f segundos\n", time);
}