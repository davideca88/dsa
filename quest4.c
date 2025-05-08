#include <stdio.h>
#include "include/avl_tree.h"

#include "include/vector.h"
#include "include/benchmark.h"
#include "include/binary_tree.h"

#define LEN 1000000

int main(){
    set_time();
    Avl rootAVL = new_avl();
    Avl rootAVL2 = new_avl();
    Avl rootAVL3 = new_avl();
    BinTree rootAB = new_bintree();
    BinTree rootAB2 = new_bintree();
    BinTree rootAB3 = new_bintree();



    
    insert_AVL_AB(LEN,10,rootAB,rootAVL,"exercicio4part1.txt");
    printf("\n");
    AB_AVL_bin(LEN,30,rootAB2,rootAVL2,"exercicio4part2.txt");
    printf("\n");
    AB_AVL_bin_sorted(LEN,1,rootAB3,rootAVL3,"exercicio4part3.txt");






    return 0;
}