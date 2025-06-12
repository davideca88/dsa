#ifndef _INDEX_H
#define _INDEX_H

#include "hash_table.h"
#include "product.h"
//#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

// Macro que pega o tamanho de um campo específico de uma struct sem instanciá-la
#define SIZEOF_FIELD(type, field) sizeof(((type*)0)->field)

#define HASH_TABLE 3
#define AVL_EQ     4
#define AVL_RANGE  5

typedef struct _index_s* Index;

struct _index_s {
    FILE*   rec_fd;
    void*   idx_p;
    char    mode;
    Product (*search)(Index idx, Key key);
    Product*(*query)(Index idx, const char* fint, Price fprice, const char* lint, Price lprice);
    bool    (*insert)(Index idx, Key key, Offset offset);
    bool    (*build)(Index idx);
    void    (*clear_query)(Product* query);
    void    (*print)(Index idx);
};

inline bool build(Index idx) {
    Product product;
    Offset offset = 0;
    rewind(idx->rec_fd);
    
    switch(idx->mode) {
        case HASH_TABLE:
            HashTable ht = (HashTable) idx->idx_p;

            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                ht->insert(ht, product.id, offset);
                offset = ftell(idx->rec_fd);
            }

            return true;
        break; // HASH_TABLE
    }
    return false;
}

inline bool hash_table_insert(Index idx, Key key, Offset offset) {
    return ((HashTable) idx->idx_p)->insert(idx->idx_p, key, offset);
}

inline Product hash_table_search(Index idx, Key key) {
    Offset offset = ((HashTable)idx->idx_p)->get(idx->idx_p, key);
    Product product = {
        .description = '\0',
        .name = '\0',
        .id = 0,
        .price = 0,
        .quantity = 0
    };
    
    fread(&product, sizeof(Product), 1, idx->rec_fd);
    
    return product;
}

inline Product avl_eq_search(Index idx, Key key);

inline bool avl_insert(Index idx, Key key, Offset offset);

Index create_index(const char* rec_name, const char* key_mode, size_t len, ...) {
    Index idx = (Index) malloc(sizeof(struct _index_s));
    
    FILE* rec_fd = fopen(rec_name, "wb+");
    
    idx->build = build;
    
    if(!strcmp(key_mode, "price")) {
        
    }

    if(!strcmp(key_mode, "id")) {
        va_list ap;
        va_start(ap, 1);
        int arg = va_arg(ap, int);
        
        switch(arg) {
            case HASH_TABLE:
                idx->idx_p = new_hash_table(len, CHAINING);
                idx->mode = HASH_TABLE;
                idx->search = hash_table_search;
                idx->insert = hash_table_insert;
                
            break; // HASH_TABLE
            case AVL_EQ:
                
            break; // AVL
            
            fclose(rec_fd);
            return idx;
        }
        
        va_end(ap);
        
        fclose(rec_fd);
        return idx;
    }
    
    fclose(rec_fd);
    
    perror("Key not recognized =(\n");
    return NULL;
}
#endif // _INDEX_H
