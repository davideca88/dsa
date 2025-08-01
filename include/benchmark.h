/*
    Equipe:
            David Lucas Lopes Caetano       (mr.aed2)
            Erick Gomes da Silva            (mr.aed1)
            Gabriel Rafael Lima Ferreira    (mr.paa)
            Vitor de Souza Oliveira         (mr.ic)


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "../include/vector.h"
#include "../include/list.h"
#include "binary_tree.h"
#include "../include/avl_tree.h"
#include "../include/index.h"
#include "../include/graph.h"

typedef int (*search) (Vector, int, int);

// Benchmark para busca binária e sequencial (vetor com tamanho fixo) - questão 01
void bm_vec_fix(Vector v, Vector keys, int len, int rep, const char* file_name, search method);

// Benchmark para busca sequencial (lista/vetor com tamanho fixo) - questão 02
void bm_listvec_fix(List l, Vector v, Vector keys, int len, int rep, const char* name);

// Benchmark para algoritmos de ordenação - questão 03-05
void bm_sortalg(int initial_size, int step, int max, int rep, const char*name);

// Benchmark para busca binária e sequencial (vetor com tamanho variado) - questão 05
void bm_vec_inc(int initial_size, int step, int max, int rep, const char* name, int ordered, search method);

// Benchmark para busca sequencial (lista/vetor com tamanho variado) - questão 05
void bm_listvec_inc(int initial_size, int step, int max, int rep, const char* name);

// Função auxiliar para selecionar rep posições em um vetor de tamanho len
void s_keys(Vector v, int len, int rep);

// Busca binária no vetor x busca na árvore binária
void bm_vec_bin(Vector v, int len, Vector keys, int reps, BinTree t, const char* name);

// Inserção na AVL e BST
void insert_AVL_AB(int len, int reps, BinTree t, Avl t2, const char* name);

//Busca Binária AVL e BST
void AB_AVL_bin(int len, int reps, BinTree t, Avl t2, const char* name);

//Busca Binária AVL e BST, inserindo de forma ordenada
void AB_AVL_bin_sorted(int len, int reps, BinTree t, Avl t2, const char* name);

//Busca para Tabela Hash, Avl e arquivo por atributo chave
void bm_keyatributte(const char* in, const char* out, int rep);

void bm_avl_file_price(const char* file_bin, const char* name, unsigned reps, Vector keys);


// Função que realiza benchmarks (testes de desempenho) das buscas BFS e DFS em grafos
// gerados com diferentes tamanhos e graus de conectividade, salvando os resultados em um arquivo.
void bm_graph(const char* name);
