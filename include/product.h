#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 80 // Constante para print_product

typedef unsigned long Key;               // Unique key for each product
typedef char          Name[64];          // Product name
typedef char          Description[256];  // Short description
typedef unsigned      Price;             // Price in cents
typedef long int      Offset;

typedef struct _product_s {
    Description description;
    Name  name;
    Key   id;
    Price price;
    unsigned short quantity;
} Product;

typedef struct _range_node_s {
    Product data;
    struct _range_node_s* next;
} RangeNode;

typedef struct _range_s* Range;
struct _range_s {
    RangeNode *head;
    RangeNode *tail;
    size_t len;
};

void print_product(Product product);
void print_range(Range range);

Range new_range();
void rappend(Range r, Product product);
void clear_range(Range r);
Product range_index(Range r, size_t index);

//Para a AVL de Keys

typedef struct keys_AVL{
    Offset offset;
    Key id;
} Keys;

//Para a AVL de Prices
typedef struct products_AVL{
    Offset offset;
    Price price;
} Prices;

#endif // _PRODUCT_H
