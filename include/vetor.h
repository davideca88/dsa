#ifndef _VETOR_H
#define _VETOR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//CODIGO AQUI:











void set_time();
void inserirVetor(int vet[], unsigned tamVet);
void mostrarVetor(int vet[], unsigned tamVet);
void meuSelectionSort(int vet[], unsigned tamVet);
void meuInsertSort (int vet[], int tamV);
void meuQuickSortR(int vet[], int inicio, int fim);
void meuQuickSort(int vet[], unsigned tamvet);
void meuMergeSortR(int vet[], int aux[], int inicio, int fim);
void meuMergeSort(int vet[], int tamVet);
void meuBubbleSort (int vet[], unsigned tamVet);
int minhaBuscaSequencialVetor(int vet[], int tamVet, int chave);
int minhaBuscaBinaria(int vet[],int tamVet,int chave);
void implementacaoBuscaSequencialVetor(int vet[], int tamVet);
void implementacaoBuscaBinaria(int vet[], int tamVet);

#endif // _VETOR_H