#include <stdio.h>
#include <string.h>
#include "../include/product.h"

int file_ssearch(const char* file, Key id){
    FILE *fd = fopen(file, "rb");
    if (!fd)
    {
        printf("Error creating file\n");
        return 0;
    }

    Product p;
    int pos;
    while (fread(&p, sizeof(Product),1,fd)==1)
    {
        if (p.id == id)
        {
            printf("Position: %d\nID: %lu\nName: %s\nDescription: %s\nPrice: %u\nQuantity: %hd\n",pos, p.id, p.name, p.description, p.price, p.quantity);
            fclose(fd);
            return 1;
        }
        pos++;
    }
    
    printf("Product ID %lu not found\n", id);
    fclose(fd);
    return 0;
}