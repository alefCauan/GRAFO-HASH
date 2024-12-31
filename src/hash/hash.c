#include "hash.h"


// Função para alocar memória para a tabela hash
HashTable* allocate_table(int table_size) {
    HashTable* table = (HashTable*)malloc(table_size * sizeof(HashTable));
    if (table == NULL) {
        fprintf(stderr, "Failed to allocate memory for the hash table.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < table_size; i++) {
        table[i].employee = NULL;
        table[i].collisions = 0;
    }
    return table;
}

// Função para desalocar memória da tabela hash
void deallocate_table(HashTable* table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        if (table[i].employee != NULL) {
            free(table[i].employee);
        }
    }
    free(table);
}

// Função para alocar memória para um funcionário
Employee* allocate_employee(const char* id, const char* name, const char* role, float salary) {
    Employee* employee = (Employee*)malloc(sizeof(Employee));
    if (employee == NULL) {
        fprintf(stderr, "Failed to allocate memory for employee.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(employee->id, id, ID_SIZE);
    strncpy(employee->name, name, sizeof(employee->name));
    strncpy(employee->role, role, sizeof(employee->role));
    employee->salary = salary;
    return employee;
}

// Função de hashing (a) - Rotação de 2 dígitos para a esquerda
int hash_a(char* id, int table_size) {
    char rotated[ID_SIZE];
    strncpy(rotated, id + 2, 4);
    strncpy(rotated + 4, id, 2);
    rotated[6] = '\0';

    int d2 = rotated[1] - '0';
    int d4 = rotated[3] - '0';
    int d6 = rotated[5] - '0';

    int sum = d2 + d4 + d6;
    return sum % table_size;
}

// Função de hashing (b) - Fold shift
int hash_b(char* id, int table_size) {
    int group1 = (id[0] - '0') * 100 + (id[2] - '0') * 10 + (id[5] - '0');
    int group2 = (id[1] - '0') * 100 + (id[3] - '0') * 10 + (id[4] - '0');

    int sum = group1 + group2;
    return sum % table_size;
}

// Insere na tabela com tratamento de colisão para hashing (a)
void insert_a(HashTable* table, int table_size, Employee employee) {
    int position = hash_a(employee.id, table_size);
    int increment = employee.id[0] - '0';

    for (int i = 0; i < table_size; i++) {
        int attempt = (position + i * increment) % table_size;
        if (table[attempt].employee == NULL) {
            table[attempt].employee = allocate_employee(employee.id, employee.name, employee.role, employee.salary);
            return;
        } else {
            table[attempt].collisions++;
        }
    }

    // Substitui na primeira posição se a tabela estiver cheia
    free(table[position].employee);
    table[position].employee = allocate_employee(employee.id, employee.name, employee.role, employee.salary);
}

// Insere na tabela com tratamento de colisão para hashing (b)
void insert_b(HashTable* table, int table_size, Employee employee) {
    int position = hash_b(employee.id, table_size);

    for (int i = 0; i < table_size; i++) {
        int attempt = (position + i * 7) % table_size;
        if (table[attempt].employee == NULL) {
            table[attempt].employee = allocate_employee(employee.id, employee.name, employee.role, employee.salary);
            return;
        } else {
            table[attempt].collisions++;
        }
    }

    // Substitui na primeira posição se a tabela estiver cheia
    free(table[position].employee);
    table[position].employee = allocate_employee(employee.id, employee.name, employee.role, employee.salary);
}

// Gera dados fictícios de funcionários
void generate_data(Employee* employees, int quantity) {
    for (int i = 0; i < quantity; i++) {
        sprintf(employees[i].id, "%06d", rand() % 1000000);
        sprintf(employees[i].name, "Employee%d", i + 1);
        sprintf(employees[i].role, "Role%d", rand() % 10);
        employees[i].salary = (rand() % 5000) + 2000;
    }
}

// Imprime estatísticas da tabela
void print_statistics(HashTable* table, int table_size) {
    int total_collisions = 0;
    int total_occupied = 0;

    for (int i = 0; i < table_size; i++) {
        if (table[i].employee != NULL) {
            total_occupied++;
        }
        total_collisions += table[i].collisions;
    }

    printf("Total occupied positions: %d\n", total_occupied);
    printf("Total collisions: %d\n", total_collisions);
}