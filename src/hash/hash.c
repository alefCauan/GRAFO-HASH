#include "hash.h"


// Função para alocar memória para a tabela hash
HashTable* allocate_table(int table_size) 
{
    HashTable* table = (HashTable*)malloc(table_size * sizeof(HashTable));

    if (table == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for the hash table.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < table_size; i++) 
    {
        table[i].employee = NULL;
        table[i].collisions = 0;
    }

    return table;
}

void deallocate_table(HashTable* table, int table_size) 
{
    for (int i = 0; i < table_size; i++) 
    {
        if (table[i].employee != NULL) 
            free(table[i].employee);
    }

    free(table);
}

// Função para alocar memória para um funcionário
Employee* allocate_employee(Employee new_employee) 
{
    Employee* employee = (Employee*)malloc(sizeof(Employee));

    if (employee == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for employee.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(employee, &new_employee, sizeof(Employee));

    return employee;
}

// Função de hashing (a) - Rotação de 2 dígitos para a esquerda
int hash_rotate(char* id, int table_size) 
{
    char rotated[ID_SIZE];

    strncpy(rotated, id + 4, 2);
    strncpy(rotated + 2, id, 4);
    rotated[6] = '\0';

    int d2 = char_to_int(rotated[1]);
    int d4 = char_to_int(rotated[3]);
    int d6 = char_to_int(rotated[5]);

    int sum = d2 + d4 + d6;

    return sum % table_size;
}



int char_to_int(char c)
{
    return c - '0';
}

// Função de hashing (b) - Fold shift
int hash_fold_shift(char* id, int table_size) 
{
    int group1 = (char_to_int(id[0])) * 100 + (char_to_int(id[2])) * 10 + (char_to_int(id[5]));
    int group2 = (char_to_int(id[1])) * 100 + (char_to_int(id[3])) * 10 + (char_to_int(id[4]));

    int sum = group1 + group2;

    return sum % table_size;
}

void insert_a(HashTable* table, int table_size, Employee employee) 
{
    int initial_pos = hash_rotate(employee.id, table_size) % table_size;
    int position = initial_pos;
    int increment = employee.id[0] - '0';
    int inserted = 0;

    do {
        if (table[position].employee == NULL) 
        {
            inserted = 1;
            table[position].employee = allocate_employee(employee);
        } 
        else 
        {
            table[position].collisions++;
            // todas as possiveis interpretações de como seria 
            // o calculo para as colisões do hash de A

            position = ((position % table_size) + increment + 1);
            // position = ((position % table_size) + 1) + increment;
            // position = position + increment;
        }
    } 
    while (!inserted && position != initial_pos && position < table_size);

    if (!inserted) 
    {
        free(table[initial_pos].employee);
        table[initial_pos].employee = allocate_employee(employee);
    }
}


void insert_b(HashTable* table, int table_size, Employee employee) 
{
    int initial_pos = hash_fold_shift(employee.id, table_size) % table_size;
    int position = initial_pos;
    int inserted = 0;

    do {
        if (table[position].employee == NULL) 
        {
            inserted = 1;
            table[position].employee = allocate_employee(employee);
        } 
        else 
        {
            table[position].collisions++;
            
            // todas as possiveis interpretações de como seria 
            // o calculo para as colisões do hash de B

            position = ((position % table_size) + 7 + 1);
            // position = ((position % table_size) + 1) + 7;
            // position = position  + 7;
        }
    } 
    while (!inserted && position != initial_pos && position < table_size);

    if (!inserted) 
    {
        free(table[initial_pos].employee);
        table[initial_pos].employee = allocate_employee(employee);
    }
}

// Gera dados fictícios de funcionários
void generate_data(Employee* employees, int quantity) 
{
    for (int i = 0; i < quantity; i++) 
    {
        sprintf(employees[i].id, "%06d", rand() % 1000000);
        sprintf(employees[i].name, "Employee%d", i + 1);
        sprintf(employees[i].role, "Role%d", rand() % 10);
        employees[i].salary = (rand() % 5000) + 2000;
    }
}

// Imprime estatísticas da tabela
void print_statistics(HashTable* table, int table_size) 
{
    int total_collisions = 0;
    int total_occupied = 0;

    for (int i = 0; i < table_size; i++) 
    {
        if (table[i].employee != NULL) 
            total_occupied++;  

        total_collisions += table[i].collisions;
    }

    printf("Total occupied positions: %d\n", total_occupied);
    printf("Total collisions: %d\n", total_collisions);
}