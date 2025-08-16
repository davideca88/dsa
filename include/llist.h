/*
    Equipe:
            David Lucas Lopes Caetano       (mr.aed2)
            Erick Gomes da Silva            (mr.aed1)
            Gabriel Rafael Lima Ferreira    (mr.paa)
            Vitor de Souza Oliveira         (mr.ic)


*/

#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>

// Tipo nó
struct llist_node {
    int data;
    struct llist_node* next;
};

typedef struct llist* LinkedList;

struct llist {
    struct llist_node *head; // Cabeça da lista
    struct llist_node *tail; // Cauda da lista
    size_t len; // Tamanho da lista
    // TODO outros dados, se necessário
};

// Cria uma lista
LinkedList new_list();

// Deleta uma lista
LinkedList delete_list(LinkedList l);

// Retorna o dado contido no index i da lista
int lindex(LinkedList l, size_t i);

// Busca sequencial na lista
char ls_search(LinkedList l, int key);

#endif /* _LIST_H */
