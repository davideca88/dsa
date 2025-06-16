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
    FILE*    rec_fd; // guarda o arquivo de registros
    void*    idx_p;  // tem o ponteiro da estrutura utilizada (Avl ou HashTable)
    Range    last_rquery; // guarda a última consulta por intervalo
    void     (*clear_last_rquery)(Index idx); // limpa a última consulta por intervalo (precisa ser rodado antes de uma nova consulta do tipo)
    Product  (*search)(Index idx, Key key); // busca por igualdade (cria um intervalo com todas as ocorrências. retorna aprimeira ocorrência)
    Range    (*rquery)(Index idx, char fint, Price fprice, char lint, Price lprice); // busca por intervalo (define last_rquery e depois retorna last_rquery)
    bool     (*insert)(Index idx, Product product); // insere (tanto no índice quanto em append no arquivo)
    bool     (*load)(Index idx); // carrega os registros no índice (é chamada após criar o índice)
    void     (*print)(Index idx); // printa os registros
    char     mode; // modo de indexação (HASH_TABLE, AVL_ID ou AVL_PRICE)
};

Index create_index(const char* rec_name, const char* key_mode, ...);

#endif // _INDEX_H
