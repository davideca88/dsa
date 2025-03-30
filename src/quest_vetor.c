#include <stdio.h>
#include "../include/vetor.h"

int main(){
    unsigned tamVet = 100;
    int vet[100];


    
    set_time();
    inserirVetor(vet,tamVet);
    printf("Vetor sem ordenar: ");
    mostrarVetor(vet,tamVet);
    implementacaoBuscaSequencial(vet,tamVet);
    //meuSelectionSort(vet,tamVet);
    meuInsertSort(vet,tamVet);
    //meuQuickSort(vet,tamVet);
    //meuMergeSort(vet,tamVet);
    //meuBubbleSort(vet,tamVet);
    printf("Vetor ordenado: ");
    mostrarVetor(vet,tamVet);
    implementacaoBuscaBinaria(vet,tamVet);

}
