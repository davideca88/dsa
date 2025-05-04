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
