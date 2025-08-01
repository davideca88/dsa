#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include "vector.h"

#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

// Nó para árvores binárias
typedef struct _node_s {
    struct _node_s* l;
    struct _node_s* r;
    uint32_t data;
} Node;

typedef Node* BinTree;

// Inicializa o nó raiz
BinTree new_bintree();

// Insere um nó na árvore
BinTree binsert(BinTree t, int data);

// Insere um nó na árvore pelo id
BinTree binsert_by_id(BinTree t, uint32_t package) ;

// Caminhamentos em ordem, pré ordem e pós ordem
void bwalk(BinTree t, void (*visit)(BinTree t), char walk_mode);

// Caminhamentos acima com varars. Semelhante à anterior, mas recebe 'n' argumentos para 'visit'  
void vbwalk(BinTree t, void(*visit)(BinTree t, size_t n, va_list args), char walk_mode, size_t n, ...);

// Transforma uma árvore t em um arquivo 
void tree_to_file(BinTree t, FILE *fd);

// Imprime os dados da árvore sem formatação
void print_tree(BinTree t,char option, char print_mode);

// Imprime os dados em decimal de um arquivo binário
void rpfile(const char* filename);

// Transfere dados do vetor para árvore binária
BinTree arvbin_vec(BinTree root, Vector v, int t, int mode);

// busca um inteiro em uma árvore 
int arvbin_Search(BinTree raiz, int d);

// Calcula a quantidade de elementos de uma árvore
int count_nodes(BinTree root);

//Altura da Arvore

int height_binTree(BinTree root);
int height_binTree(BinTree root);

//Esvazia a BST

void delete_BST(BinTree t);

#endif // _BINARY_TREE_H 
