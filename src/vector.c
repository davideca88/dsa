//feito pelo maior coder do mundo, mr.aed.

// melhorado por aquele que é melhor, mr.aed II

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "../include/vector.h"


int* new_vector(size_t rep) {
    int *v = (int*) malloc(sizeof(int) * rep);
    return v;
}

void set_time(){

    srand(time(NULL));
    
}


void randomize(Vector v, unsigned rep){
    int x;

    for(unsigned i = 0; i < rep; i++){
        x = rand() % (rep*10);
        v[i] = x; 
    }
}

void sorted_arr(int *arr, unsigned rep){
    arr[0] = rand() % 20;

    for (unsigned i = 0; i < rep; i++)
    {
        arr[i] = arr[i-1] + (rand() % 20+1);
    }
}

void print_v(Vector v, unsigned rep){
    unsigned i;
    printf("[");
    printf("%d", v[0]);
    for(i = 1; i < rep; i++){
        
        printf(", %d", v[i]);
    }
    printf("]\n");
}


void s_sort(Vector v, unsigned rep){
    unsigned i, j, min_pos; 
    int tmp;

    for(i = 0; i < rep-1; i++){
        min_pos = i;

        for(j = i+1; j < rep; j++){
            if(v[j] < v[min_pos]){
                min_pos = j;
            }
        }

        tmp = v[i];
        v[i] = v[min_pos];
        v[min_pos] = tmp;

    }

}


void i_sort (Vector v, int rep){
    int i,j,pivot;

    for(i = 1; i < rep; i++){
        pivot = v[i];
        j = i-1;

        while((j>=0)&&(pivot < v[j])){
            v[j+1] = v[j];
            j--;
        }

        v[j+1] = pivot;
    }
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
  
  

  
void q_sort(Vector v, unsigned rep) {
    q_sortR(v,0, rep-1);
    i_sort(v,rep);
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
  
  

void m_sort(Vector v, int rep) {
    int *aux;
  
    aux =    (int*) malloc( sizeof(int)*rep);
  
    m_sortR(v, aux, 0, rep-1);
  
    free(aux);
}


void b_sort (Vector v, unsigned rep) {
    unsigned k, j; 
    int tmp;

    for (k = 1; k < rep; k++) {

        for (j = 0; j < rep - 1; j++) {

            if (v[j] > v[j + 1]) {
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }

        }
    }
}



int s_search(Vector v, int rep, int key){
    int i;
    for(i = 0; i < rep; i++){

        if(key == v[i]){
            return i;
        }

    }

    return -1;
}


int b_search(Vector v,int rep,int key){
    int mid, beg = 0, end = rep-1;

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

void bb_search(Vector v, unsigned len, unsigned rep, const char* file_name){
    FILE* file = fopen(file_name, "w");
    if (file == NULL)
    {
        printf("error creating file");
        return;
    }

    fprintf(file, "Execucao, tempo(s), pos, valor\n");

    clock_t beg, end;
    double times[rep];
    double sum = 0.0;

    char used[len];
    memset(used, 0, sizeof(used));


    for (unsigned i = 0; i < rep; i++)
    {
        int key;
        do
        {
            key = rand() % len; 
        } while (used[key]);
        
        used[key] = 1;

        beg = clock();
        b_search(v, len, key);
        end = clock();

        double time = ((double)(end-beg))/CLOCKS_PER_SEC;
        times[i] = time;
        sum += time;

        fprintf(file, "%d,     %.6f,  %d,  %d\n", i+1, time, key, v[key]);
    }

    double average = sum/rep;
    double variance = 0.0;

    for (unsigned i = 0; i < rep; i++)
    {
        variance += pow(times[i]-average,2);
    }

    double s_dev = sqrt(variance/(rep-1));

    fprintf(file,"media: %.6f\n",average);
    fprintf(file,"desvio padrao: %.7f\n", s_dev);

    fclose(file);
    printf("Arquivo salvo");
}
/*

void implementacaoBuscaSequencialVetor(Vector v, int rep){
    int result, random_num;

    random_num = rand() % rep;

    result = s_search(v,rep,v[random_num]);

    if(result){

        printf("usando busca sequencial encontrei o %d na posicao %d\n",v[result],result);

    }
    

}



void implementacaoBuscaBinaria(Vector v, int rep){
    int result, random_num;

    random_num = rand() % rep;

    result = b_search(v,rep,v[random_num]);

    if(result){

        printf("usando busca binaria encontrei o %d na posicao %d\n",v[result],result);
        
    }

}



*/
