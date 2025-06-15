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


#define HASH_TABLE 3
#define AVL_ID     4
#define AVL_PRICE  5

typedef struct _index_s* Index;
struct _index_s {
    FILE*    rec_fd;
    void*    idx_p;
    Range    last_rquery;
    Product  (*search)(Index idx, Key key);
    Range    (*rquery)(Index idx, char fint, Price fprice, char lint, Price lprice);
    bool     (*insert)(Index idx, Product product);
    bool     (*load)(Index idx);
    void     (*print)(Index idx);
    char     mode;
};

bool load(Index idx);

bool hash_table_insert(Index idx, Product product);

Product hash_table_search(Index idx, Key key);

Product avl_eq_search(Index idx, Key key);

bool avl_eq_insert(Index idx, Product product);

Range avl_rquery(Index idx, char fint, Price fprice, char lint, Price lprice);

Index create_index(const char* rec_name, const char* key_mode, ...);

#endif // _INDEX_H
