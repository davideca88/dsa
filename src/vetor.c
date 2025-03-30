//feito pelo maior coder do mundo mr.aed

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vetor.h"


void set_time(){

    srand(time(NULL));
    
}
/*
Função que insere numeros aleatorios num vetor de n posicoes, 
usando a função rand e time das bibliotecas stdlib time respectivamente.
*/

void inserirVetor(int vet[], unsigned tamVet){
    int x;

    for(unsigned i = 0; i < tamVet; i++){
        x = rand() % (tamVet*10);
        vet[i] = x; 
    }
}

// Função de mostrar vetor para testes.
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


/* Versão 2
usa a constante limiarInsercao (setada acima como 60) para o 
quickSortR2 passar a ordenar apenas pedaços maiores que 60.
O vetor fica parcialmente ordenado e a ordenação termina com a chamada para a
ordenação por inserção
implementa também a otimização proposta por Robert Sedgewick que mencionei hoje
*/


void meuQuickSortR(int vet[], int inicio, int fim) {
    int i,j;
    int pivot;  // do mesmo tipo da minha chave de ordenacao (ou dos elem. de v)
    int tmp; // do mesmo tipo dos elementos do vetor
    int meio;
    while(fim -inicio > 60) {
      meio = (inicio+fim)/2;
      pivot =  vet[meio];
      i= inicio;
      j = fim;
      while(i <=j) {    // WHILE NO LUGAR DO IF QUE NORMALMENTE APARECERIA AQUI
        while(vet[i] < pivot) { i++;}  // avanca enquanto está do lado certo
        while(vet[j] > pivot) { j--;} // recua enquanto está do lado certo
        if(i <=j ) {
      tmp  = vet[i];
      vet[i] = vet[j];
      vet[j] = tmp;
      i++;
      j--;
        } 
      }
      if(j < meio)  {  // DECIDE QUE LADO VAI TER CHAMADA RECURSIVA E QUE LADO VAI SER TRATADO NESTA MESMA CHAMADA
        meuQuickSortR(vet,inicio,j); // Lado esquerdo é tratado com chamada recursiva
        inicio = i;  // Lado direito é tratado sem chamar recursivamente
      }
      else {
        meuQuickSortR(vet,i, fim); // Lado direito é tratado com chamada recursiva
        fim = j;   // Lado direito é tratado sem chamar recursivamente
      }
    }
}
  
  
/* usa a versão 2 e ordena por inserção para completar o trabalho
experimentem pra ver como fica mais rápido */
  
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



int minhaBuscaSequencial(int vet[], int tamVet, int chave){
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

void implementacaoBuscaSequencial(int vet[], int tamVet){
    int result, num_aleatorio;

    num_aleatorio = rand() % tamVet;

    result = minhaBuscaSequencial(vet,tamVet,vet[num_aleatorio]);

    if(result){

        printf("encontrei o %d na posicao %d\n",vet[result],result);

    }

    

}


void implementacaoBuscaBinaria(int vet[], int tamVet){
    int result, num_aleatorio;

    num_aleatorio = rand() % tamVet;

    result = minhaBuscaBinaria(vet,tamVet,vet[num_aleatorio]);

    if(result){

        printf("encontrei o %d na posicao %d\n",vet[result],result);
        
    }

}




