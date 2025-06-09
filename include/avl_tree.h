#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h> 

#include "../include/vector.h"
#include "../include/product.h"

#define max(A, B) ((A > B) ? A : B)

#define PREORDER  0
#define INORDER   1
#define POSTORDER 2

// Nó para árvore avl
typedef struct _avl_node_s {
    struct _avl_node_s* l;
    struct _avl_node_s* r;
    keys data;
    int8_t height;
} AvlNode;

typedef AvlNode* Avl;

// Inicializa uma árvore avl
Avl new_avl();

// Insere na árvore avl
Avl avl_insert(Avl t, keys data);

// Busca a subárvore que possui data
Avl avl_search(const char* nomeArquivo, Avl t, Key id);

// Retorna o tamanho da árvore
int8_t avl_height(Avl t);

// Função de caminhamento na árvore 
void avl_walk(Avl t, void (*visit)(Avl), char walk_mode);

void avl_walk2(Avl t,const char* nomeArquivo, char walk_mode);

// Imprime uma árvore avl
void avl_print(const char* nomeArquivo, Avl t, char print_mode);

//Passa valores de um vetor para uma AVL
//Avl avl_vec(Avl root, Vector v, size_t t);

//Esvazia a AVL
void delete_AVL(Avl t);


//Funções AVL de Prices

typedef struct _avl_node_price_s {
    struct _avl_node_price_s* l;
    struct _avl_node_price_s* r;
    struct _avl_node_price_s* d;
    prices data;
    int8_t height;
} AvlNodePrices;

typedef AvlNodePrices* AvlPrices;

//Cria uma AVL de prices
AvlPrices new_avl_Prices();


AvlPrices avl_prices_insert(AvlPrices t, prices data);

AvlPrices avl_prices_search(const char* nomeArquivo, AvlPrices t, Price price);

int8_t avl_prices_height(AvlPrices t);

void avl_prices_walk(AvlPrices t,const char* nomeArquivo, char walk_mode);

void avl_prices_walk2(AvlPrices t, void(*visit)(AvlPrices t), char walk_mode);


void avl_prices_print(const char* nomeArquivo, AvlPrices t, char print_mode);




void delete_AVL_prices(AvlPrices t);


Avl criarAVLDeIndicesKey(const char* nomeArquivo, Avl t);

AvlPrices criarAVLDeIndicesPrices(const char* nomeArquivo, AvlPrices t);

void printInOrderWithConditions(const char* nomeArquivo, AvlPrices t, unsigned min, unsigned max, bool includeMin, bool includeMax);

void printRange(const char* nomeArquivo, AvlPrices t, unsigned min, unsigned max, bool includeMin, bool includeMax);





#endif // _AVL_TREE_H
