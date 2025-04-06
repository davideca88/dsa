#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/vector.h"

// Tipo nó
typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct _list_s* List;

struct _list_s {
    Node *head; // Cabeça da lista
    Node *tail; // Cauda da lista
    size_t len; // Tamanho da lista
    // TODO outros dados, se necessário
};

// Cria uma lista
List new_list();

// Deleta uma lista
List delete_list(List l);

// Retorna o dado contido no index i da lista
int lindex(List l, size_t i);

// Transforma um vetor em uma lista. Retorna o tamanho da lista se conseguiu criar. Se não, retorna INT_MAX
size_t array_to_list(List l, Vector arr, size_t arr_len);

// Busca sequencial na lista
char lb_search(List l, int key);

#endif /* _LIST_H */
