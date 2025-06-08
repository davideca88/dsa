#include "include/hash_table.h"


int main() {
    HashTable ht = new_hash_table(10, CHAINING);
    
    ht->insert(ht, 10, 50);
    ht->insert(ht, 10, 51);
    ht->insert(ht, 15, 55);
    ht->insert(ht, 25, 75);
    ht->insert(ht, 35, 69);

    print_hash_table(ht);

    printf("Chave 25: %li\n", ht->get(ht, 25));
    
    return 0;
}
