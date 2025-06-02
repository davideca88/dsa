#include <math.h>
#include "../include/hash_table.h"

// pod-si-matá

unsigned hash(Key key, size_t ht_len) {
    unsigned hash;

    hash = key * key;

    return 0;
}

char chaining_insert(HashTable ht, Data data);
Data chaining_get(HashTable ht, Key key);

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
