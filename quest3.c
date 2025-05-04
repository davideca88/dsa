#include <stdio.h>
#include <time.h>
#include "../include/benchmark.h"




#define len 1000000

int main(){
    
    srand(time(NULL));
    BinTree root = new_bintree();
    int reps = 30;
    Vector v = new_vector(len);
    Vector keys = new_vector(reps);

    randomize(v,len); // vetor randomizado
    s_keys(keys,len,reps);

    // Questão 3: busca binária vetor x busca em árvore binária
    bm_vec_bin(v,len,keys,reps,root,"exercicio3.txt");
    
}
  
