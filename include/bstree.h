#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

// Nó para árvores binárias
struct bst_node {
    struct bst_node* l;
    struct bst_node* r;
    int data;
};

typedef struct bst_node* Bst;

// Inicializa o nó raiz
Bst new_bst();

// Insere um nó na árvore
Bst bst_insert(Bst t, int data);

// Caminhamentos em ordem, pré ordem e pós ordem
void bst_walk(Bst t, void (*visit)(Bst t), char walk_mode);

// Caminhamentos acima com varars. Semelhante à anterior, mas recebe 'n' argumentos para 'visit'  
void vbst_walk(Bst t, void(*visit)(Bst t, size_t n, va_list args), char walk_mode, size_t n, ...);

// busca um inteiro em uma árvore 
int bst_search(Bst raiz, int d);

// Calcula a quantidade de elementos de uma árvore
int bst_count_nodes(Bst root);

//Altura da Arvore
int bst_height(Bst root);

//Esvazia a BST
Bst delete_bst(Bst t);

#endif // _BINARY_TREE_H 
