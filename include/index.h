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

// Constantes para query()
#define LT 10 // menor que
#define LE 11 // menor ou igual que
#define GT 12 // maior que
#define GE 13 // maior ou igual que

typedef struct _index_s* Index;

struct _index_s {
    FILE*   rec_fd;
    void*   idx_p;
    char    mode;
    Product (*search)(Index idx, Key key);
    Product*(*query)(Index idx, char fint, Price fprice, char lint, Price lprice);
    bool    (*insert)(Index idx, Key key, Offset offset);
    bool    (*build)(Index idx);
    void    (*clear_query)(Product* query);
    void    (*print)(Index idx);
};

bool build(Index idx) {
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

Product* avl_query(Index idx, char fint, Price fprice, char lint, Price lprice);

Index create_index(const char* rec_name, const char* key_mode, size_t len, ...) {
    FILE* rec_fd = fopen(rec_name, "wb+");

    if(!rec_fd) {
        perror("Falha ao abrir arquivo de registros =(\n");
        return NULL;
    }
    
    Index idx = (Index) malloc(sizeof(struct _index_s));

    idx->rec_fd = rec_fd;
    idx->query = avl_query;
    idx->build = build;
    
    if(!strcmp(key_mode, "price")) {
        
    }

    if(!strcmp(key_mode, "id")) {
        va_list ap;
        va_start(ap, len);
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
            
            default:
                perror("Tipo de índice por \"id\" não reconhecido=(\n");
                free(idx);
                return NULL;
            break;
        }
        
        va_end(ap);
        
        return idx;
    }
    
    perror("Modo de indexação não reconhecido =(\n");
    free(idx);
    return NULL;
}
#endif // _INDEX_H
