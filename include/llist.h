/*
    Equipe:
            David Lucas Lopes Caetano       (mr.aed2)
            Erick Gomes da Silva            (mr.aed1)
            Gabriel Rafael Lima Ferreira    (mr.paa)
            Vitor de Souza Oliveira         (mr.ic)


*/

#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>
#include "types.h"

// Tipo nó
struct llist_node {
    void *data;
    struct llist_node* next;
};

struct llist {
    struct llist_node *head; // Cabeça da lista
    struct llist_node *tail; // Cauda da lista
    size_t data_size;
    size_t len; // Tamanho da lista
    // TODO outros dados, se necessário
};

// Cria uma lista
static inline struct llist *_llist_init(size_t data_size);

#define llist_init(type) \
    _llist_init(sizeof(type))

// Deleta uma lista
struct llist *delete_llist(struct llist *l);

// Insere um elemento na lista encadeada
void llist_insert_head(struct llist *l, void *data);

// Retorna o dado contido no index i da lista
void *llist_index(struct llist *l, size_t i);

// Busca sequencial na lista
char llist_search(struct llist *l, const void* key, comp_fn cmp);

#endif /* _LIST_H */
