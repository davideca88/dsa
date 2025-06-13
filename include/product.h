#ifndef _PRODUCT_H
#define _PRODUCT_H

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
