#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Retorna o tamanho da lista
size_t llen(List l); 

// Insere na cabeça (head) da lista
int linserth(List l, int data);

// Insere na cauda (tail) da lista
int linsertt(List l, int data);

// Remove um nó de índice. Retorna o dado do nó removido. Retorna INT_MAX se não encontrar o elemento
int lremove(List l, size_t i);

// Imprime a lista no stdout e retorna o tamanho da lista
size_t print_list(List l);

// Transforma um vetor em uma lista
size_t array_to_list(List l, int arr[], size_t arr_len);

#endif /* _LIST_H */
