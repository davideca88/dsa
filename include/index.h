#ifndef _INDEX_H
#define _INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "hash_table.h"
#include "product.h"
#include "avl_tree.h"

// Macro que pega o tamanho de um campo específico de uma struct sem instanciá-la
#define SIZEOF_FIELD(type, field) sizeof(((type*)0)->field)

#define HASH_TABLE 3
#define AVL_EQ     4
#define AVL_RANGE  5

typedef struct _index_s* Index;

struct _index_s {
    FILE*    rec_fd;
    void*    idx_p;
    Range last_rquery;
    char     mode;
    Product  (*search)(Index idx, Key key);
    bool  (*rquery)(Index idx, char fint, Price fprice, char lint, Price lprice);
    bool     (*insert)(Index idx, Product product);
    bool     (*load)(Index idx);
    void     (*print)(Index idx);
};


bool load(Index idx);

bool hash_table_insert(Index idx, Product product);

Product hash_table_search(Index idx, Key key);

//inline Product avl_eq_search(Index idx, Key key);

//inline bool avl_insert(Index idx, Product product, Offset offset);

//Product* avl_query(Index idx, char fint, Price fprice, char lint, Price lprice);

Index create_index(const char* rec_name, size_t len, const char* key_mode, ...);

#endif // _INDEX_H
