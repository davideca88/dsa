#include <stdio.h>

#include "include/index.h"
#include "include/product.h"

int main() {

    Index idx = create_index("products2.bin", "price");
    idx->load(idx);
    
//    print_product(idx->search(idx, 900));

    Product test = {
        .name = "Produto novo ultra mega power clone do clone caro e 3",
        .description = "Descrição super mega hiper detalhada gigantesca unica e exclusivamente feita para testar a minha função de imprimir produto que quebra as linhas automaticamente assim que o paragrafo atinge o limite de 80 colunas wooow. pra testar duplicata de novoo",
        .quantity = 60,
        .price = 6900,
        .id = 420
    };

    test = idx->search(idx, 75);
    puts("\nPrimeira ocorrência de busca por preço 75.00:\n");
    print_product(test);
    puts("\navl range no intervalo [0-70]\n");
    idx->rquery(idx, 1, 0, 1, 70);
    print_range(idx->last_rquery);

    Index idx2 = create_index("products2.bin", "id", AVL_ID);
    idx2->load(idx2);

    puts("\navl id:\n");
    idx2->print(idx2);
    Index idx3 = create_index("products2.bin", "id", HASH_TABLE, 10007);
    idx3->load(idx3);

    puts("\nhash_table:\n");
    idx3->print(idx3);

    return 0;
}
