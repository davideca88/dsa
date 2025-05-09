#include <stdio.h>
#include <time.h>

#include "include/vector.h"
#include "include/binary_tree.h"

#define LEN 500
#define DISORDER 0
#define DUPLICATE 0
#define MAX_ID ((1 << 18)-1)

int main(){
    if (LEN > MAX_ID)
    {
        printf("The number of packets exceeds the 18-bit limit! (262143 packets)\n");
        return 0;
    }
    
    set_time();

    Vector packages = new_vector(LEN);
    BinTree root = new_bintree();

    printf("IMPORTANT INFORMATION\nPACKETS: IDENTIFIER (18 BITS) + DATA (14 BITS)\nDISORDER: %d%%  DUPLICATE: %d%%\n",DISORDER, DUPLICATE);
    printf("**-------------------------------------------**\n");
    puts("#I1\nRECEIVED DATA PACKETS:\n");
    gen_packages(packages, LEN, DISORDER, DUPLICATE);
    clock_t beg = clock();
    root = arvbin_vec(root,packages,LEN,1);
    clock_t end = clock();
    double time = ((double)(end-beg))/CLOCKS_PER_SEC;
    int total_nodes = count_nodes(root);
    int height = height_binTree(root);

    printf("\n**-------------------------------------------**\n");
    puts("#I2\nBINARY SEARCH TREE:\n");
    puts("IN-ODRDER:\n");
    print_tree(root,1, INORDER);
    printf("**-------------------------------------------**\n");
    printf("#R2\nTOTAL: %d PACKETS\nBST SIZE: %lu BYTES\nPACKAGE SIZE: %lu BYTES\nPACKAGE RECEIVE TIME: %.7lf SEC\nBST HEIGHT:%d\n",total_nodes,sizeof(root)*total_nodes,total_nodes*sizeof(packages[0]),time,height);
    printf("**-------------------------------------------**\n");

    FILE *fd = fopen("packages.bin","wb");
    if (fd == NULL)
    {
        printf("Error creating file\n");
        return 0;
    }
    tree_to_file(root,fd);
    printf("PACKAGE.BIN SAVED\n");
    printf("**-------------------------------------------**\n");
    fclose(fd);

    puts("#I3\nPACKAGE.BIN DATA (FROM BINARY ARCHIVE):\n");
    rpfile("packages.bin");
    printf("**---------------------END--------------------**\n");

    return 0;
}