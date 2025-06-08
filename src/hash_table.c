//#include <math.h>
#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro que pega o tamanho de um campo específico de uma struct sem instanciá-la
// #define SIZEOF_FIELD(type, field) sizeof(((type*)0)->field)

// pod-si-matá

size_t hash(Key key, size_t len) {
    return (key * key * PRIME) % len;
}

bool chaining_insert(HashTable this, Key key, size_t offset) {

    if(!this) {
        perror("Tabela inexistente =(\n");
        return false;
    }
    
    size_t data_hash = hash(key, this->len);
    struct _hash_table_chaining_node_s \
            *new_bucket_node = (struct _hash_table_chaining_node_s*) \
                    malloc(sizeof(struct _hash_table_chaining_node_s));
    
    if(!new_bucket_node) {
        perror("Falha ao criar novo bucket =(\n");
        return false;
    }
    
/* o índice faz isso
    strncpy(new_product->description, data.description, SIZEOF_FIELD(Offset, description));
    strncpy(new_product->name, data.name, SIZEOF_FIELD(Offset, name));
    new_product->id = data.id;
    new_product->price = data.price;
    new_product->quantity = data.quantity;
*/
    new_bucket_node->bucket.key = key;
    new_bucket_node->bucket.offset = offset;
    new_bucket_node->next = NULL; 

    struct _hash_table_chaining_node_s **table = \
            (struct _hash_table_chaining_node_s**) this->table;
     
    struct _hash_table_chaining_node_s *tmp = table[data_hash], **aux = &(table[data_hash]);
 
    if(tmp == NULL) {
        *aux = new_bucket_node;
        return true;
    }

    while(tmp->next) tmp = tmp->next; 

    aux = &(tmp->next);
    *aux = new_bucket_node;
        
    return true;
}

Offset chaining_get(HashTable this, Key key) {
    size_t data_hash = hash(key, this->len);

    struct _hash_table_chaining_node_s **table = \
            (struct _hash_table_chaining_node_s**) this->table;

    struct _hash_table_chaining_node_s* aux = table[data_hash];
    
    while(aux) {
        if(aux->bucket.key == key)
            return aux->bucket.offset;
        aux = aux->next;
    }

    return EOF;
}

bool overflow_area_insert(HashTable this, Key key, size_t offset);
Offset oveflow_area_get(HashTable this, Key key);


HashTable new_hash_table(size_t len, char collision_mode) {
    HashTable ht = (HashTable) malloc(sizeof(struct _hash_table_s));
/*  trabalho do índice
    FILE *hash_table_index_fd = fopen("idxs/id.idx", "w");
    FILE *products_rec_fd     = fopen("products.rec", "ab+");
    
    
    if(!products_rec_fd) {
        perror("Falha ao abrir arquivo de registros =(\n");
        return NULL;
    }

    if(!hash_table_index_fd) {
        perror("Falha ao abrir arquivo de índice por ID =(\n");
        return NULL;
    }
    
    fseek(products_rec_fd, 0, SEEK_END);
*/

    ht->len = len;
    ht->collision_mode = collision_mode;
    
    switch (collision_mode) {
        case CHAINING:
            ht->table = calloc(len, sizeof(struct _hash_table_chaining_node_s*));
            ht->get = chaining_get;
            ht->insert = chaining_insert;
        break; // CHAINING
/*
        case OVERFLOW_AREA:
            ht->table = calloc(len + (len / 10), sizeof(Bucket*));
            ht->get = oveflow_area_get;
            ht->insert = overflow_area_insert;
        break; // OVERFLOW_AREA
*/
        default:
            perror("Collision mode not recognized =(\n");
            return NULL;
        break; // default
    }

    return ht;
}

void print_hash_table(HashTable ht) {
    switch (ht->collision_mode) {
        case CHAINING:
            struct _hash_table_chaining_node_s **table = \
                    (struct _hash_table_chaining_node_s**) ht->table;
            putchar('[');
            
            struct _hash_table_chaining_node_s *aux = table[0];
            size_t i = 0;
            
            for(; i < ht->len; i++, aux = table[i]) {
                if(aux) {
                    printf("%lu: %ld", aux->bucket.key, aux->bucket.offset);
                    aux = aux->next;
                    break;
                } 
            }
            for(; i < ht->len; i++, aux = table[i]) {
                while(aux) {
                    printf(",\n %lu: %ld", aux->bucket.key, aux->bucket.offset);
                    aux = aux->next;
                }
            }
            puts("]");
        break; // CHAINING
    }
}
