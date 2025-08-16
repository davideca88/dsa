#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CHAINING      0
#define OVERFLOW_AREA 1

#define PRIME 0x9E3779B1

typedef unsigned long Key;
typedef unsigned long Offset; 

typedef struct _bucket_s{
    Offset offset;
    Key key;
} Bucket;

// Nó para hash table com colisão de lista encadeada
struct _hash_table_chaining_node_s {
    Bucket bucket;
    struct _hash_table_chaining_node_s *next;
};

// HashTable genérico com funções de inserir e buscar um elemento
typedef struct _hash_table_s* HashTable;
struct _hash_table_s {
    void    *table;
    Offset (*get)(HashTable ht, Key key); 
    bool   (*insert)(HashTable ht, Key key, size_t offset);
    size_t  len;
    char collision_mode;
};

// Função de espalhamento. Deve ser chamado em todas as funções do tipo 'get'
size_t hash(Key key, size_t len);

// Funções para hash table encadeado
bool    chaining_insert(HashTable ht, Key key, size_t offset);
Offset chaining_get(HashTable ht, Key key);

// Funções para overflow area
bool    overflow_area_insert(HashTable ht, Key key, size_t offset);
Offset oveflow_area_get(HashTable ht, Key key);

// Cria tabela especificando tamanho e método de tratamento de colisão
HashTable new_hash_table(size_t len, char collision_mode);

#endif // _HASH_TABLE_H

/*

#include "include/hash_table.h"

int main() {
    Bucket data = {
                    123, // chave
                    10   // dado
    };
    
    // hash table chaining com 10 células
    HashTable ht = new_hash_table(10, CHAINING);
        
    ht->insert(ht, data);

    Bucket data2 = ht->get(ht, 123);
    
    return 0;
}

*/
