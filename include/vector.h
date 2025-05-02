/*
    Equipe:
            David Lucas Lopes Caetano       (mr.aed2)
            Erick Gomes da Silva            (mr.aed1)
            Gabriel Rafael Lima Ferreira    (mr.paa)
            Vitor de Souza Oliveira         (mr.ic)


*/

#ifndef _VETOR_H
#define _VETOR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//CODIGO AQUI:

typedef int* Vector;

void set_time();

// Cria um vetor de tamanho len
int* new_vector(size_t len);

int* delete_vector(Vector v);

// Aleatoriza um vetor
void randomize(Vector v, unsigned len);

// Preenche ordenamente um vetor
void sorted_arr(Vector v, unsigned len);

// Gera pacotes para a árvore binária de busca
int gen_packages(Vector packages, int len);

// Imprime um vetor
void print_v(Vector v, unsigned len);

// Copia vetores
void copy_vec(Vector orgin, Vector dest, size_t len);

// Selection sort
void s_sort(Vector v, unsigned len);

// Insertion sort
void i_sort (Vector v, int len);

// Quick sort (parte recursiva)
void q_sortR(Vector v, int beg, int end);

// Quick sort original
void q_sort(Vector v, unsigned len);

// Quick sort com insertion
void q_sortv2(Vector v, unsigned len);

// Merge sorr (parte recursiva)
void m_sortR(Vector v, int aux[], int beg, int end);

// Merge sort
void m_sort(Vector v, int len);

// Bubble sort
void b_sort (Vector v, unsigned len);

// Busca sequencial no vetor
int  s_search(Vector v, int len, int key);

// Busca binária no vetor
int  b_search(Vector v,int len,int key);

// void implementacaoBuscaSequencialVetor(Vector v, int len);
// void implementacaoBuscaBinaria(Vector v, int len);

#endif // _VETOR_H;
