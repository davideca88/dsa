
/*
 * Nesse commit, esse arquivo não possui serventia nenhuma
 * Ele só tá aqui por motivos de "não sei"
 */

#include "../include/llist.h"

#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

// Deleta uma lista
struct llist *llist_free(struct llist *l) {
    struct llist_node *node = l->head;
    struct llist_node *next;

    while(node) {
        next = node->next;
        free(node);
        node = next;
    }
    
    return NULL;
}

static inline struct llist_node *llist_node_create(const void *data, \
                                                         size_t data_size) {
    struct llist_node *new;
    new->next = NULL;
    
    new = (struct llist_node*) malloc(sizeof(struct llist_node));
    check_allocation(new);
    
    new->data = malloc(data_size);
    check_allocation(new->data);

    return new;
}

// Insere na cauda (tail) da lista
void llist_insert_tail(struct llist *l, void *data) {
    struct llist_node *node = (struct llist_node*) malloc(sizeof(struct llist_node));
    node->data = malloc(l->data_size);

    node->next = NULL;
    
    if(l->tail) {
        l->tail->next = node;
    } else {
        l->head = node;
    }
    l->tail = node;
    
    l->len++;
}

void llist_insert_head(struct llist *l, void *data) {
        
}

/*
// Imprime a lista no stdout e retorna o tamanho da lista
size_t print_llist(struct llist *l) {
    struct llist_node *node;
    putchar('[');
    
    if(l->len) {
        node = l->head;
        printf("%d", node->data);
        node = node->next;
        
        while(node) {
            printf(", %d", node->data);
            node = node->next;
        }
    }
    
    putchar(']');
    
    return l->len;
}
*/

/*

// Retorna o dado contido no index i da lista
void *llist_index(struct llist *l, size_t i) {
    struct llist_node *node = l->head;
    size_t pos = 0;

    while(pos < i) {
        node = node->next;
        pos++;
    }
    
    return node->data;
}

*/

/*
// Busca sequencial na lista. Retorna bool se encontrou ou não
char lls_search(struct llist *l, void *key, comp_fn cmp) {
    struct llist_node *node = l->head;
    while(node && (*cmp)(node->data, key) != 0) {
        node = node->next;
    }
    if(node) {
        return 1;
    }
    return 0;
}
*/
