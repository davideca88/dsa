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
#include <limits.h>
#include "../include/vector.h"

// Tipo nó
typedef struct node2 {
    int data;
    struct node2* next;
} Node2;

typedef struct _list_s* List;

struct _list_s {
    Node2 *head; // Cabeça da lista
    Node2 *tail; // Cauda da lista
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
size_t vector_to_list(Vector v, List l, size_t v_len);

// Busca sequencial na lista
char ls_search(List l, int key);

#endif /* _LIST_H */
