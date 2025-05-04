#include <stdio.h>
#include <time.h>
#include "../include/benchmark.h"
#include "include/vector.h"
#include "include/binary_tree.h"




#define LEN 1000000

int main(){
    
    srand(time(NULL));
    BinTree root = new_bintree();
    int reps = 30;
    Vector v = new_vector(LEN);
    Vector keys = new_vector(reps);

    randomize(v,LEN); // vetor randomizado
    s_keys(keys,LEN,reps);

    // Questão 3: busca binária vetor x busca em árvore binária
    bm_vec_bin(v,LEN,keys,reps,root,"exercicio3.txt");
    
}
  
