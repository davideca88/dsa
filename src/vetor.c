//feito pelo maior coder do mundo, mr.aed.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vetor.h"


void set_time(){

    srand(time(NULL));
    
}


void inserirVetor(int vet[], unsigned tamVet){
    int x;

    for(unsigned i = 0; i < tamVet; i++){
        x = rand() % (tamVet*10);
        vet[i] = x; 
    }
}


void mostrarVetor(int vet[], unsigned tamVet){
    unsigned i;
    printf("[");
    printf("%d",vet[0]);
    for(i = 1; i < tamVet; i++){
        
        printf(", %d",vet[i]);
    }
    printf("]\n");
}


void meuSelectionSort(int vet[], unsigned tamVet){
    unsigned i, j, pos_menor; 
    int tmp;

    for(i = 0; i < tamVet-1; i++){
        pos_menor = i;

        for(j = i+1; j < tamVet; j++){
            if(vet[j] < vet[pos_menor]){
                pos_menor = j;
            }
        }

        tmp = vet[i];
        vet[i] = vet[pos_menor];
        vet[pos_menor] = tmp;

    }

}


void meuInsertSort (int vet[], int tamVet){
    int i,j,pivot;

    for(i = 1; i < tamVet; i++){
        pivot = vet[i];
        j = i-1;

        while((j>=0)&&(pivot < vet[j])){
            vet[j+1] = vet[j];
            j--;
        }

        vet[j+1] = pivot;
    }
}




void meuQuickSortR(int vet[], int inicio, int fim) {
    int i,j;
    int pivot;  
    int tmp; 
    int meio;
    while(fim -inicio > 60) {
      meio = (inicio+fim)/2;
      pivot =  vet[meio];
      i= inicio;
      j = fim;
      while(i <=j) {    
        while(vet[i] < pivot) { i++;}  
        while(vet[j] > pivot) { j--;} 
        if(i <=j ) {
      tmp  = vet[i];
      vet[i] = vet[j];
      vet[j] = tmp;
      i++;
      j--;
        } 
      }
      if(j < meio)  {  
        meuQuickSortR(vet,inicio,j); 
        inicio = i;  
      }
      else {
        meuQuickSortR(vet,i, fim);
        fim = j;  
      }
    }
}
  
  

  
void meuQuickSort(int vet[], unsigned tamvet) {
    meuQuickSortR(vet,0, tamvet-1);
    meuInsertSort(vet,tamvet);
}




void meuMergeSortR(int vet[], int aux[], int inicio, int fim) {
    int a,b,k;
    if(inicio < fim) {
  
      int meio = (inicio+fim)/2;
      meuMergeSortR(vet, aux, inicio, meio);
      meuMergeSortR(vet, aux, meio+1, fim);
    
      a = inicio;  b = meio+1;   k = inicio;
      while((a <= meio) && (b<=fim)) {
        if(vet[a] < vet[b]) {    aux[k] = vet[a];      a++;    }
        else            {    aux[k] = vet[b];      b++;    }
        k++;
      }
      while(a <= meio) {    aux[k] = vet[a];    a++; k++;  }
      while(b <= fim) {    aux[k] = vet[b];    b++;    k++;  }
      for(k = inicio; k <= fim; k++) { vet[k] = aux[k]; }
    }
}
  
  

void meuMergeSort(int vet[], int tamVet) {
    int *aux;
  
    aux =    (int*) malloc( sizeof(int)*tamVet);
  
    meuMergeSortR(vet, aux, 0, tamVet-1);
  
    free(aux);
}


void meuBubbleSort (int vet[], unsigned tamVet) {
    unsigned k, j; 
    int tmp;

    for (k = 1; k < tamVet; k++) {

        for (j = 0; j < tamVet - 1; j++) {

            if (vet[j] > vet[j + 1]) {
                tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
            }

        }
    }
}



int minhaBuscaSequencialVetor(int vet[], int tamVet, int chave){
    int i;
    for(i = 0; i < tamVet; i++){

        if(chave == vet[i]){
            return i;
        }

    }

    return -1;
}


int minhaBuscaBinaria(int vet[],int tamVet,int chave){
    int meio, inicio = 0, fim = tamVet-1;

    while(inicio <= fim){

        meio = (inicio+fim)/2;

        if(chave > vet[meio]){

            inicio = meio+1;

        }
        else if(chave < vet[meio]){

            fim = meio-1;

        }
        else{

            return meio;

        }


    }

    return -1;
}

void implementacaoBuscaSequencialVetor(int vet[], int tamVet){
    int result, num_aleatorio;

    num_aleatorio = rand() % tamVet;

    result = minhaBuscaSequencialVetor(vet,tamVet,vet[num_aleatorio]);

    if(result){

        printf("usando busca sequencial encontrei o %d na posicao %d\n",vet[result],result);

    }

    

}


void implementacaoBuscaBinaria(int vet[], int tamVet){
    int result, num_aleatorio;

    num_aleatorio = rand() % tamVet;

    result = minhaBuscaBinaria(vet,tamVet,vet[num_aleatorio]);

    if(result){

        printf("usando busca binaria encontrei o %d na posicao %d\n",vet[result],result);
        
    }

}




