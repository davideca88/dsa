#include <stdio.h>
#include "include/avl_tree.h"

#include "include/vector.h"
#include "include/benchmark.h"
#include "include/binary_tree.h"

#define LEN 10000000

int main(){
    set_time();
    Avl root = new_avl();
    BinTree root2 = new_bintree();



    insert_AVL_AB(LEN,10,root2,root,"exercicio4part1.txt");
    printf("\n");
    AB_AVL_bin(LEN,30,root2,root,"exercicio4part2.txt");
    printf("\n");

    

    


    return 0;
}