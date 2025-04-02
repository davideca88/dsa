#ifndef _VETOR_H
#define _VETOR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//CODIGO AQUI:

// Configura rand()
void set_time();
// Aleatoriza um vetor
void randomize(int arr[], unsigned len);
// Preence ordenamente um vetor
void sorted_arr(int *arr, unsigned len);
// Imprime um vetor
void print_arr(int arr[], unsigned len);
// Selection sort
void s_sort(int arr[], unsigned len);

// Insertion sort
void i_sort (int arr[], int len);

// Quick sort (parte recursiva)
void q_sortR(int arr[], int inicio, int fim);

// Quick sort
void q_sort(int arr[], unsigned len);

// Merge sorr (parte recursiva)
void m_sortR(int arr[], int aux[], int inicio, int fim);

// Merge sort
void m_sort(int arr[], int len);

// Bubble sort
void b_sort (int arr[], unsigned len);

// Busca sequencial no vetor
int  s_search(int arr[], int len, int chave);

// Busca binária no vetor
int  b_search(int arr[],int len,int chave);

// void implementacaoBuscaSequencialVetor(int arr[], int len);
// void implementacaoBuscaBinaria(int arr[], int len);

#endif // _VETOR_H
