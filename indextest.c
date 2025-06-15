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

    test = idx->search(idx, 69);
    puts("Primeira ocorrência:");
    print_product(test);
    puts("avl range");
    print_range(idx->last_rquery);

    Index idx2 = create_index("products2.bin", "id", HASH_TABLE, 10007);
    idx2->load(idx2);

    puts("avl id:");
    idx2->print(idx2);
    Index idx3 = create_index("products2.bin", "id", HASH_TABLE, 10007);
    idx3->load(idx3);

    puts("hash_table:");
    idx3->print(idx3);

    return 0;
}
