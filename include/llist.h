/*
 *
 * Cabeçalho que contém uma API de listas simplesmente encadeadas
 *
 */

#ifndef _LLIST_H
#define _LLIST_H

#include <stddef.h>

#include "macros.h"



struct llist_node {
    struct llist_node *next;
};

struct llist_head {
    struct llist_node *first;
};


/*
 * LLIST_HEAD - cria uma cabeça — marcador — de lista
 *
 * @name:       nome da cabeça
 *
 * A cabeça não possui dados além de dados da lista. Ela atua apenas como
 * marcador do início da lista. Por isso, não faz sentido querer usar
 * operações de remoção nesse nó.
 */
#define LLIST_HEAD(name) \
    struct llist_head (name)

/*
 * LLIST_ENTRY - acha o endereço da struct (ou typedef)* instanciada que contém o nó
 * 
 * @ptr:        ponteiro do nó conhecido
 * @type:       struct (*) que contém o nó
 * @name:       nome da variável do tipo struct llist_node* dentro da struct (*)
 */
#define LLIST_ENTRY(ptr, type, name) \
    CONTAINER_OF(ptr, type, name)

/*
 * LLIST_FOR_EACH - itera sobre toda a lista
 *
 * @head:       cabeça da lista
 * @pos:        elemento que será iterado
 */
#define LLIST_FOR_EACH(head, pos) \
    for(pos = head.first; pos; pos = pos->next)

/*
 * llist_head_init - inicializa a cabeça da lista
 */
static inline struct llist_head llist_head_init(void) {
    return (struct llist_head) { .first = NULL };
}

/*
 * llist_insert - insere uma sublista no início de outra
 *
 * @prev:       antecessor da sublista que será inserida
 * @new_head:   cabeçada sublista
 * @new_tail:   calda da sublista
 * @pos:        sucessor da sublista
 */
static inline void llist_insert(struct llist_head *head, \
                struct llist_node *new_head, struct llist_node *new_tail) {
    new_tail->next = head->first;
    head->first = new_head;
}


/*
 * llist_bremoval - faz um bulk removal. Remove uma sublista do início da lista
 *
 * @prev:       antecessor da sublista que será removida
 * @new_tail:   calda da sublista
 * @pos:        sucessor da sublista
 *
 * Retorna o elemento cabeça da sublista removida
 */
static inline struct llist_node *llist_bremoval(struct llist_head *head, \
                        struct llist_node *rem_tail) {
    struct llist_node *rem_head = head->first;
    
    head->first = rem_tail->next;
    rem_tail->next = NULL;

    return rem_head;
}

/*
 * llist_add - insere um elemento após a cabeça da lista
 *
 * @head:       cabeça da lista
 * @new:        nó que será inserido
 */
static inline void llist_add(struct llist_head *head, struct llist_node *new) {
    llist_insert(head, new, new);
}

/*
 * llist_remove - remove um elemento após a cabeça da lista
 *
 * @head:       cabeça da lista
 * @rem:        nó que será removido
 *
 * Retorna o endereço do nó removido
 */
static inline struct llist_node *llist_remove(struct llist_head *head, \
                                                      struct llist_node *rem) {
    return llist_bremoval(head, rem);
}


#endif /* _LLIST_H */
