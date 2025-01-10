#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

int main() 
{
    srand(time(NULL));

    Employee employees[MAX_EMPLOYEES];
    generate_data(employees, MAX_EMPLOYEES);

    int sizes[] = {101, 150};

    for (int t = 0; t < 2; t++) 
    {
        int table_size = sizes[t];

        printf("\nHash Table with %d positions:\n", table_size);

        // Hashing (a)
        HashTable *table_a = allocate_table(table_size);
        for (int i = 0; i < MAX_EMPLOYEES; i++) 
            insert_a(table_a, table_size, employees[i]);
        
        printf("Hashing (a):\n");
        print_statistics(table_a, table_size);
        deallocate_table(table_a, table_size);

        // Hashing (b)
        HashTable* table_b = allocate_table(table_size);
        for (int i = 0; i < MAX_EMPLOYEES; i++) 
            insert_b(table_b, table_size, employees[i]);
        
        printf("Hashing (b):\n");
        print_statistics(table_b, table_size);
        deallocate_table(table_b, table_size);
    }

    return 0;
}
