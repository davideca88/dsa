#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

typedef struct _node_s {
    struct _node_s* l;
    struct _node_s* r;
    int data;
} Node;

typedef Node* BinTree;

// Inicializa o nó raiz
BinTree new_bintree();

// Insere um nó na árvore
BinTree binsert(BinTree t, int data);

// Caminhamentos em ordem, pré ordem e pós ordem
void bwalk(BinTree t, void (*visit)(BinTree t), char walk_mode);

// Imprime os dados da árvore sem formatação
void print_tree(BinTree t, char print_mode);

#endif // _BINARY_TREE_H 
