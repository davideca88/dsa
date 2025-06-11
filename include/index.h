#ifndef _INDEX_H
#define _INDEX_H

#include "hash_table.h"
//#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

// Macro que pega o tamanho de um campo específico de uma struct sem instanciá-la
#define SIZEOF_FIELD(type, field) sizeof(((type*)0)->field)

#define HASH_TABLE 3
#define AVL        4

typedef struct _index_s* Index;

struct _index_s {
    FILE* rec_fd;
    void* idx_p;
    char idx_mode;
    Offset (*search)(Index idx, Key key);
    bool (*insert)(Index idx, Key key, Offset offset);
    void (*destroy)(Index idx);
    void (*print)(Index idx);
};

inline bool hash_table_insert(Index idx, Key key, Offset offset) {
    return ((HashTable) idx->idx_p)->insert(idx->idx_p, key, offset);
}

inline Offset hash_table_search(Index idx, Key key) {
    return ((HashTable)idx->idx_p)->get(idx->idx_p, key);
}

Index create_index(const char* rec_name, const char* key_mode, size_t len, ...) {
    Index idx = (Index) malloc(sizeof(struct _index_s));
    
    FILE* rec_fd = fopen(rec_name, "wb+");
    
    if(!strcmp(key_mode, "price")) {
        
    }

    if(!strcmp(key_mode, "id")) {
        va_list ap;
        va_start(ap, 1);
        int arg = va_arg(ap, int);
        
        switch(arg) {
            case HASH_TABLE:
                idx->idx_p = new_hash_table(len, CHAINING);
                idx->search = hash_table_search;
                idx->insert = hash_table_insert;
                
            break; // HASH_TABLE
            case AVL:
                
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
