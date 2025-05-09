//feito pelo maior coder do mundo, mr.aed.

// melhorado por aquele que é melhor, mr.aed II

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "../include/vector.h"

#define MAX_DATA  ((1 << 14) - 1)
#define MAX_ID    ((1 << 18) - 1)

int* new_vector(size_t len) {
    int *v = (int*) malloc(sizeof(int) * len);
    return v;
}

int* delete_vector(Vector v) {
    free(v);
    return NULL;
}

void set_time(){

    srand(time(NULL));
    
}

void randomize(Vector v, unsigned len){
    int x;

    for(unsigned i = 0; i < len; i++){
        x = rand() % (len*10);
        v[i] = x; 
    }
}

void sorted_arr(Vector v, unsigned len){
    v[0] = rand() % 20;

    for (unsigned i = 1; i < len; i++)
    {
        v[i] = v[i-1] + (rand() % 20+1);
    }
}

void copy_vec(Vector orgin, Vector dest, size_t len){
    memcpy(dest,orgin,len*sizeof(int));
}

void print_v(Vector v, unsigned len){
    unsigned i;
    printf("[");
    printf("%d", v[0]);
    for(i = 1; i < len; i++){
        
        printf(", %d", v[i]);
    }
    printf("]\n");
}


void s_sort(Vector v, unsigned len){
    unsigned i, j, min_pos; 
    int tmp;

    for(i = 0; i < len-1; i++){
        min_pos = i;

        for(j = i+1; j < len; j++){
            if(v[j] < v[min_pos]){
                min_pos = j;
            }
        }

        tmp = v[i];
        v[i] = v[min_pos];
        v[min_pos] = tmp;

    }

}


void i_sort (Vector v, int len){
    int i,j,pivot;

    for(i = 1; i < len; i++){
        pivot = v[i];
        j = i-1;

        while((j>=0)&&(pivot < v[j])){
            v[j+1] = v[j];
            j--;
        }

        v[j+1] = pivot;
    }
}


void q_sortR2(Vector v, int beg, int end) {
    int i,j;
    int pivot;
    int tmp;

    pivot =  v[(beg+end)/2];
    i= beg;
    j = end;
    while(i <=j) {
        while(v[i] < pivot) { i++;} 
        while(v[j] > pivot) { j--;} 
        if(i <=j ) {
            tmp  = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--;
        } 
    }
    if(beg < j)  q_sortR2(v,beg,j);
    if(i < end) q_sortR2(v,i,end);
}


void q_sortR(Vector v, int beg, int end) {
    int i,j;
    int pivot;  
    int tmp; 
    int mid;
    while(end -beg > 60) {
      mid = (beg+end)/2;
      pivot =  v[mid];
      i= beg;
      j = end;
      while(i <=j) {    
        while(v[i] < pivot) { i++;}  
        while(v[j] > pivot) { j--;} 
        if(i <=j ) {
      tmp  = v[i];
      v[i] = v[j];
      v[j] = tmp;
      i++;
      j--;
        } 
      }
      if(j < mid)  {  
        q_sortR(v,beg,j); 
        beg = i;  
      }
      else {
        q_sortR(v,i, end);
        end = j;  
      }
    }
}
  
  
void q_sort(Vector v, unsigned len){
    q_sortR2(v, 0, len-1);
}
  
void q_sortv2(Vector v, unsigned len) {
    q_sortR(v,0, len-1);
    i_sort(v,len);
}




void m_sortR(Vector v, int aux[], int beg, int end) {
    int a,b,k;
    if(beg < end) {
  
      int mid = (beg+end)/2;
      m_sortR(v, aux, beg, mid);
      m_sortR(v, aux, mid+1, end);
    
      a = beg;  b = mid+1;   k = beg;
      while((a <= mid) && (b<=end)) {
        if(v[a] < v[b]) {    aux[k] = v[a];      a++;    }
        else            {    aux[k] = v[b];      b++;    }
        k++;
      }
      while(a <= mid) {    aux[k] = v[a];    a++; k++;  }
      while(b <= end) {    aux[k] = v[b];    b++;    k++;  }
      for(k = beg; k <= end; k++) { v[k] = aux[k]; }
    }
}
  
  

void m_sort(Vector v, int len) {
    int *aux;
  
    aux =    (int*) malloc( sizeof(int)*len);
  
    m_sortR(v, aux, 0, len-1);
  
    free(aux);
}


void b_sort (Vector v, unsigned len) {
    unsigned k, j; 
    int tmp;

    for (k = 1; k < len; k++) {

        for (j = 0; j < len - 1; j++) {

            if (v[j] > v[j + 1]) {
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }

        }
    }
}



int s_search(Vector v, int len, int key){
    int i;
    for(i = 0; i < len; i++){

        if(key == v[i]){
            return i;
        }

    }

    return -1;
}


int b_search(Vector v,int len,int key){
    int mid, beg = 0, end = len-1;

    while(beg <= end){

        mid = (beg+end)/2;

        if(key > v[mid]){

            beg = mid+1;

        }
        else if(key < v[mid]){

            end = mid-1;

        }
        else{

            return mid;

        }


    }

    return -1;
}

void print_package(uint32_t package) {
    int id = (package >> 14); 
    int data = (package & MAX_DATA);
    printf("ID: %d DATA: %d\n", id, data);
}

/*
Gera os pacotes para a árvore binária de busca;
Cada pacote é composto: Identificador(18 bits) + dado(14 bits);
*/
int gen_packages(Vector packages, int len, int dis, int dup){
    if(len>MAX_ID)return 0;
    int disorder = (dis * len) / 100;
    uint32_t id = 0;
    int count = 0;
    clock_t beg,end;

    beg = clock();
    for (int i = 0; i < len; i++) {
        uint32_t info = rand() % (MAX_DATA + 1);

        uint32_t package = ((id & MAX_ID) << 14) | (info & MAX_DATA);
        packages[i] = package;
        id++;

        if ((i + 1 < len) && (rand() % 100 < dup)) {
            i++, count++;
            packages[i] = package;
        }
    }

    for (int i = 0; i < disorder; i++) {
        int ind1 = rand() % len;
        int ind2 = rand() % len;

        int temp = packages[ind1];
        packages[ind1] = packages[ind2];
        packages[ind2] = temp;
    }
    end = clock();
    double time = ((double)(end-beg))/CLOCKS_PER_SEC;


    for (int i = 0; i < len; i++)
    {
        print_package(packages[i]);
    }

    printf("**-------------------------------------------**\n");
    printf("#R1\n");
    printf("TOTAL: %d PACKETS\nSIZE: %lu BYTES\nRETRANSMISSION: %d PACKETS\nPACKAGE TRANSMISSION TIME: %.7lf SEC",len,len*sizeof(packages[0]),count,time);

    
    return 0;
}

/*

void implementacaoBuscaSequencialVetor(Vector v, int len){
    int result, random_num;

    random_num = rand() % len;

    result = s_search(v,len,v[random_num]);

    if(result){

        printf("usando busca sequencial encontrei o %d na posicao %d\n",v[result],result);

    }
    

}



void implementacaoBuscaBinaria(Vector v, int len){
    int result, random_num;

    random_num = rand() % len;

    result = b_search(v,len,v[random_num]);

    if(result){

        printf("usando busca binaria encontrei o %d na posicao %d\n",v[result],result);
        
    }

}



*/
