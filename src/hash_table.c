//#include <math.h>
#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

// pod-si-matá

unsigned hash(Key key, size_t ht_len) {
    return (key * key * PRIME) % ht_len;
}

char chaining_insert(HashTable ht, Data data) {
    Data *new = (Data*) malloc(sizeof(Data));

    struct _hash_table_chaining_node_s \
        *new_node = (struct _hash_table_chaining_node_s*) \
           malloc(sizeof(struct _hash_table_chaining_node_s));

    strncpy(new->description, data.description, sizeof(data.description));
    strncpy(new->name, data.name, sizeof(data.name));
    new->id = data.id;
    new->price = data.price;
    new->quantity = data.quantity;

    new_node->data = new;
    new_node->next = NULL;
   
    unsigned data_hash = hash(data.id, ht->len);

    struct _hash_table_chaining_node_s **table_ptr = (struct _hash_table_chaining_node_s**) ht->table;

// fazendo samerda aqui
    
    if(table_ptr[data_hash] != NULL)
    
    return 0;
}
Data chaining_get(HashTable ht, Key key);

char overflow_area_insert(HashTable ht, Data data);
Data oveflow_area_get(HashTable ht, Key key);


HashTable new_hash_table(size_t len, char collision_mode) {
    HashTable ht = (HashTable) malloc(sizeof(struct _hash_table_s));

    switch (collision_mode) {
        case CHAINING:
            ht->table = calloc(len, sizeof(struct _hash_table_chaining_node_s*));
            ht->get = chaining_get;
            ht->insert = chaining_insert;
            ht->len = len;
        break; // CHAINING

        case OVERFLOW_AREA:
            ht->table = calloc(len + (len / 10), sizeof(Data*));
            ht->get = oveflow_area_get;
            ht->insert = overflow_area_insert;
            ht->len = len;
        break; // OVERFLOW_AREA

        default:
            perror("Collision mode not recognized =(\n");
            exit(EXIT_FAILURE);
        break; // default
    }

    return ht;
}
