#include <stdio.h>
#include "include/avl_tree.h"

#include "include/vector.h"
#include "include/benchmark.h"
#include "include/binary_tree.h"

#define LEN 1000000

int main(){
    set_time();
    Avl rootAVL = new_avl();
    BinTree rootAB = new_bintree();


    insert_AVL_AB(LEN,10,rootAB,rootAVL,"exercicio4part1.txt");
    printf("\n");
    
    AB_AVL_bin(LEN,30,rootAB,rootAVL,"exercicio4part2.txt");
    printf("\n");
    
    AB_AVL_bin_sorted(160000,30,rootAB,rootAVL,"exercicio4part3.txt");
    puts("\n");




   




    return 0;
}