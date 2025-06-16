#include "../include/hash_table.h"

size_t hash(Key key, size_t len) {
    return (key * PRIME) % len;
}

bool chaining_insert(HashTable this, Key key, size_t offset) {

    if(!this) {
        puts("Tabela inexistente =(");
        return false;
    }
    
    size_t data_hash = hash(key, this->len);
    struct _hash_table_chaining_node_s \
            *new_bucket_node = (struct _hash_table_chaining_node_s*) \
                    malloc(sizeof(struct _hash_table_chaining_node_s));
    
    if(!new_bucket_node) {
        puts("Falha ao criar novo bucket =(");
        return false;
    }
    
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

bool overflow_area_insert(HashTable this, Key key, size_t offset) {
    if(!this) {
        puts("Tabela inexistente =(");
        return false;
    }

    size_t data_hash = hash(key, this->len);
    Bucket *new_bucket = (Bucket*) malloc(sizeof(Bucket));
    
    if(!new_bucket) {
        puts("Falha ao criar novo bucket =(");
        return false;
    }
    
    new_bucket->offset = offset;
    new_bucket->key = key;

    Bucket **table = (Bucket**) this->table;

    if(table[data_hash] == NULL) {
        table[data_hash] = new_bucket;
        return true;
    }

    for(size_t i = this->len; i < (this->len + (this->len / 10)); i++) {
        if(table[i] == NULL) {
            table[i] = new_bucket;
            return true;
        }
    }

    puts("Tabela cheia =("); // provavelmente devemos redimencionar a tabela, mas preguiça
    return false;
}

Offset oveflow_area_get(HashTable this, Key key) {
    size_t data_hash = hash(key, this->len);
    Bucket **table = (Bucket**) this->table;

    if(!table[data_hash])
        return EOF;

    if(table[data_hash]->key == key) {
        return table[data_hash]->offset;
    }

    for(size_t i = this->len; i < (this->len + (this->len / 10)); i++) {
        if(table[i]->key == key) {
            return table[i]->offset;
        }
    }

    return EOF;
}


HashTable new_hash_table(size_t len, char collision_mode) {
    HashTable ht = (HashTable) malloc(sizeof(struct _hash_table_s));

    ht->len = len;
    ht->collision_mode = collision_mode;
    
    switch (collision_mode) {
        case CHAINING:
            ht->table = calloc(len, sizeof(struct _hash_table_chaining_node_s*));
            ht->get = chaining_get;
            ht->insert = chaining_insert;
        break; // CHAINING

        case OVERFLOW_AREA:
            ht->table = calloc(len + (len / 10), sizeof(Bucket*));
            ht->get = oveflow_area_get;
            ht->insert = overflow_area_insert;
        break; // OVERFLOW_AREA

        default:
            puts("Collision mode not recognized =(");
            return NULL;
        break; // default
    }

    return ht;
}

