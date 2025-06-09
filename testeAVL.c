#include "include/product.h"
#include "include/avl_tree.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>







int main(){

//    VAI PRINTAR MUITO NÚMERO, O ARQUIVO .BIN TEM 10MIL PRODUTOS PARA TESTE

//    SE QUISER MENOS, COLOCA O "products2.bin", TEM 4 PRODUTOS PARA TESTE
    
    Avl t = new_avl();

    t = criarAVLDeIndicesKey("products.bin",t);

    avl_print("products.bin",t,1);

    avl_search("products.bin",t,10000);

    delete_AVL(t);


    printf("AVL deletado\n");



    AvlPrices t2 = new_avl_Prices();

    t2 = criarAVLDeIndicesPrices("products.bin",t2);

    avl_prices_print("products.bin",t2,1);

    avl_prices_search("products.bin",t2,350);


    printRange("products.bin",t2,300,400,0,0);


    delete_AVL_prices(t2);


    printf("AVL de prices deletado\n");





}