/*
 * Funções ficarão brevemente por aqui por questões de facilidade
 * depois haverá um .c separado para elas
 *
 * fazendo só pra dar uma adiantada e vocês entenderem como vai ser
 * a arquitetura do trabalho
 * 
 *
 * no final tem um pequeno código de exemplo
*/

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>

#define CHAINING      0
#define OVERFLOW_AREA 1

// Tipos dado e chave (a definir). Aqui tem um exemplo bem simples
typedef unsigned long Key;
typedef struct _data_s {
    Key key;
    int data;
} Data;

// Nó para hash table com colisão de lista encadeada
struct _hash_table_chaining_node_s {
    Data *data;
    Data *next;
};

// HashTable genérico com funções de inserir e buscar um elemento
typedef struct _hash_table_s* HashTable;
struct _hash_table_s {
    void *table;
    Data (*get)(HashTable ht, Key key); 
    char (*insert)(HashTable ht, Data data);
};

// Função de espalhamento. Deve ser chamado em todas as funções do tipo 'get'
unsigned hash(Key key);

// Funções para hash table encadeado
char chaining_insert(HashTable ht, Data data);
Data chaining_get(HashTable ht, Key key);

// Funções para overflow area
char overflow_area_insert(HashTable ht, Data data);
Data oveflow_area_get(HashTable ht, Key key);
 
HashTable new_hash_table(size_t len, char collision_mode) {
    HashTable ht = (HashTable) malloc(sizeof(struct _hash_table_s));

    switch (collision_mode) {
        case CHAINING:
            ht->table = malloc(sizeof(struct _hash_table_chaining_node_s*) * len);
            ht->get = chaining_get;
            ht->insert = chaining_insert;
        break; // CHAINING

        case OVERFLOW_AREA:
            ht->table = malloc(sizeof(Data*) * len);
            ht->get = oveflow_area_get;
            ht->insert = overflow_area_insert;
        break; // OVERFLOW_AREA

        // Outros casos devem ser implementados no futuro

        default:
            perror("Collision mode not recognized =(\n");
            exit(EXIT_FAILURE);
        break; // default
    }

    return ht;
}

#endif // _HASH_TABLE_H

/*

#include "include/hash_table.h"

int main() {
    Data data = {
                    123, // chave
                    10   // dado
    };
    
    // hash table chaining com 10 células
    HashTable ht = new_hash_table(10, CHAINING);
        
    ht->insert(ht, data);

    Data data2 = ht->get(ht, 123);
    
    return 0;
}

*/
