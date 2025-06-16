#include <stdio.h>

#include "include/index.h"
#include "include/product.h"

int main() {

    Index idx = create_index("./un10k_products.bin", "price");
    idx->load(idx);
    
//    print_product(idx->search(idx, 900));

    puts("\navl range no intervalo [0-250]\n");
    idx->rquery(idx, 1, 0, 1, 250);
    print_range(idx->last_rquery);

    printf("qtd 1: %ld\n", idx->last_rquery->len);
    idx->clear_last_rquery(idx);
    printf("qtd 2: %ld\n", idx->last_rquery->len);
   
    getchar();
    
    puts("\navl range no intervalo [500-800]\n");
    idx->rquery(idx, 1, 0, 1, 1100);
    print_range(idx->last_rquery);
    printf("qtd 3: %ld\n", idx->last_rquery->len);
    idx->clear_last_rquery(idx);

    idx->rquery(idx, 1, 0, 1, 250);
    print_range(idx->last_rquery);

    printf("qtd 1: %ld\n", idx->last_rquery->len);
/*    Index idx2 = create_index("products2.bin", "id", AVL_ID);
    idx2->load(idx2);

    puts("\navl id:\n");
    idx2->print(idx2);
    Index idx3 = create_index("products2.bin", "id", HASH_TABLE, 10007);
    idx3->load(idx3);

    puts("\nhash_table:\n");
    idx3->print(idx3);
*/
    return 0;
}
