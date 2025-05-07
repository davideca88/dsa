#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/vector.h"

#define max(A, B) ((A > B) ? A : B)

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
Avl avl_search(Avl t, uint32_t data);

// Retorna o tamanho da árvore
int8_t avl_height(Avl t);

//Passa valores de um vetor para uma AVL

Avl avl_vec(Avl root, Vector v, size_t t);

#endif // _AVL_TREE_H
/*

//Avl avlinsert(Avl t, uint32_t data) {
//    return _avlinsert(t, data, 0);
//}
   
Avl avl_l_rotation(Avl t) {
    Avl aux;
    aux = t->r;
    t->r = aux->l;
    aux->l = t;
    return aux;
}
Avl avl_l_rotation(Avl t) {
    Avl aux;
    
    aux = t->r;
    t->r = aux->r;
    aux->r = t->l;
    t->l = aux;

    return t;
}

Avl avl_r_rotation(Avl t) {
    Avl aux;
    
    aux = t->l;
    t->l = aux->l;
    aux->l = t->r;
    t->r = aux;
    
    return t;
}

Avl avl_rl_rotation(Avl t) {
    avl_r_rotation(t->r);
    avl_l_rotation(t);

    return t;
}

Avl avl_lr_rotation(Avl t) {
    avl_l_rotation(t->l);
    avl_r_rotation(t);

    return t;
}

*/
