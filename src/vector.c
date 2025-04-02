//feito pelo maior coder do mundo, mr.aed.

// melhorado por aquele que é melhor, mr.aed II

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vector.h"


void set_time(){

    srand(time(NULL));
    
}


void randomize(int arr[], unsigned len){
    int x;

    for(unsigned i = 0; i < len; i++){
        x = rand() % (len*10);
        arr[i] = x; 
    }
}


void print_arr(int arr[], unsigned len){
    unsigned i;
    printf("[");
    printf("%d",arr[0]);
    for(i = 1; i < len; i++){
        
        printf(", %d",arr[i]);
    }
    printf("]\n");
}


void s_sort(int arr[], unsigned len){
    unsigned i, j, min_pos; 
    int tmp;

    for(i = 0; i < len-1; i++){
        min_pos = i;

        for(j = i+1; j < len; j++){
            if(arr[j] < arr[min_pos]){
                min_pos = j;
            }
        }

        tmp = arr[i];
        arr[i] = arr[min_pos];
        arr[min_pos] = tmp;

    }

}


void i_sort (int arr[], int len){
    int i,j,pivot;

    for(i = 1; i < len; i++){
        pivot = arr[i];
        j = i-1;

        while((j>=0)&&(pivot < arr[j])){
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = pivot;
    }
}




void q_sortR(int arr[], int beg, int end) {
    int i,j;
    int pivot;  
    int tmp; 
    int mid;
    while(end -beg > 60) {
      mid = (beg+end)/2;
      pivot =  arr[mid];
      i= beg;
      j = end;
      while(i <=j) {    
        while(arr[i] < pivot) { i++;}  
        while(arr[j] > pivot) { j--;} 
        if(i <=j ) {
      tmp  = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
        } 
      }
      if(j < mid)  {  
        q_sortR(arr,beg,j); 
        beg = i;  
      }
      else {
        q_sortR(arr,i, end);
        end = j;  
      }
    }
}
  
  

  
void q_sort(int arr[], unsigned len) {
    q_sortR(arr,0, len-1);
    i_sort(arr,len);
}




void m_sortR(int arr[], int aux[], int beg, int end) {
    int a,b,k;
    if(beg < end) {
  
      int mid = (beg+end)/2;
      m_sortR(arr, aux, beg, mid);
      m_sortR(arr, aux, mid+1, end);
    
      a = beg;  b = mid+1;   k = beg;
      while((a <= mid) && (b<=end)) {
        if(arr[a] < arr[b]) {    aux[k] = arr[a];      a++;    }
        else            {    aux[k] = arr[b];      b++;    }
        k++;
      }
      while(a <= mid) {    aux[k] = arr[a];    a++; k++;  }
      while(b <= end) {    aux[k] = arr[b];    b++;    k++;  }
      for(k = beg; k <= end; k++) { arr[k] = aux[k]; }
    }
}
  
  

void m_sort(int arr[], int len) {
    int *aux;
  
    aux =    (int*) malloc( sizeof(int)*len);
  
    m_sortR(arr, aux, 0, len-1);
  
    free(aux);
}


void b_sort (int arr[], unsigned len) {
    unsigned k, j; 
    int tmp;

    for (k = 1; k < len; k++) {

        for (j = 0; j < len - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }

        }
    }
}



int s_search(int arr[], int len, int key){
    int i;
    for(i = 0; i < len; i++){

        if(key == arr[i]){
            return i;
        }

    }

    return -1;
}


int b_search(int arr[],int len,int key){
    int mid, beg = 0, end = len-1;

    while(beg <= end){

        mid = (beg+end)/2;

        if(key > arr[mid]){

            beg = mid+1;

        }
        else if(key < arr[mid]){

            end = mid-1;

        }
        else{

            return mid;

        }


    }

    return -1;
}
/*

void implementacaoBuscaSequencialVetor(int arr[], int len){
    int result, random_num;

    random_num = rand() % len;

    result = s_search(arr,len,arr[random_num]);

    if(result){

        printf("usando busca sequencial encontrei o %d na posicao %d\n",arr[result],result);

    }
    

}



void implementacaoBuscaBinaria(int arr[], int len){
    int result, random_num;

    random_num = rand() % len;

    result = b_search(arr,len,arr[random_num]);

    if(result){

        printf("usando busca binaria encontrei o %d na posicao %d\n",arr[result],result);
        
    }

}



*/
