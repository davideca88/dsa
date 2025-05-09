#include <stdio.h>
#include <time.h>

#include "include/vector.h"
#include "include/binary_tree.h"

#define LEN 20


int main(int argc, char* argv[]) {
    
    set_time();
    
    BinTree root = new_bintree();

    for(size_t i = 0; i < LEN; i++) {
        root = binsert(root, rand() % (LEN * 10));
    }
    
    puts("Impressão da árvore:\n\tPré-ordem:\n");
    print_tree(root,0, PREORDER);

    puts("\n\tEm-ordem:\n");
    print_tree(root,0, INORDER);

    puts("\n\tPós-ordem:\n");
    print_tree(root,0, POSTORDER);
    puts("\n");

    return 0;
}
