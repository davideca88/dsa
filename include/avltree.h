#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "types.h"

#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

// Nó para árvore avl
typedef struct _avl_node_s {
    struct _avl_node_s* l;
    struct _avl_node_s* r;
    uint32_t data;
    int8_t height;
} AvlNode;

typedef AvlNode* Avl;

// Inicializa uma árvore avl
Avl new_avl();

// Insere na árvore avl
Avl avl_insert(Avl t, uint32_t data);

// Busca a subárvore que possui data
Avl avl_search(Avl t, uint32_t);

// Retorna o tamanho da árvore
int8_t avl_height(Avl t);

// Função de caminhamento na árvore 
void avl_walk(Avl t, void (*visit)(Avl), char walk_mode);

// Imprime uma árvore avl
void avl_print(Avl t, char print_mode);

//Esvazia a AVL
void delete_avl(Avl t);
#endif // _AVL_TREE_H
