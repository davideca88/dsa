#include <stdio.h>
#include <time.h>

#include "include/vector.h"
#include "include/binary_tree.h"

#define LEN 10

int main(){
    set_time();

    Vector packages = new_vector(LEN);
    BinTree root = new_bintree();

    gen_packages(packages, LEN);
    printf("Os pacotes são compostos: Identificador (n algarismos) + dado (4 últimos algarismos)\n");
    printf("Pacotes recebidos: ");
    print_v(packages,LEN);

    for (int i = 0; i < LEN; i++)
    {
        root = binsert(root, packages[i]);
    }

    printf("**-------------------------------------------**\n");
    puts("Impressão da árvore:\n\tPré-ordem:\n");
    print_tree(root, PREORDER);

    puts("\n\tEm-ordem:\n");
    print_tree(root, INORDER);

    puts("\n\tPós-ordem:\n");
    print_tree(root, POSTORDER);
    printf("\n**-------------------------------------------**\n");

    FILE *fd = fopen("packages.bin","wb");
    if (fd == NULL)
    {
        printf("Error creating file\n");
        return 0;
    }

    tree_to_file(root,fd);

    return 0;
}