#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMPLOYEES 1000
#define ID_SIZE 7 // Inclui \0

typedef struct {
    char id[ID_SIZE];
    char name[50];
    char role[50];
    float salary;
} Employee;

typedef struct {
    Employee* employee;
    int collisions;
} HashTable;

int char_to_int(char c);
HashTable* allocate_table(int table_size);
void deallocate_table(HashTable* table, int table_size);
Employee* allocate_employee(Employee new_employee);
int hash_rotate(char* id, int table_size);
int hash_fold_shift(char* id, int table_size);
void insert_a(HashTable* table, int table_size, Employee employee);
void insert_b(HashTable* table, int table_size, Employee employee);
void generate_data(Employee* employees, int quantity);
void print_statistics(HashTable* table, int table_size);

#endif
