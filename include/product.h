#ifndef _PRODUCT_H
#define _PRODUCT_H

typedef unsigned long Key;               // Unique key for each product
typedef char          Name[64];          // Product name
typedef char          Description[256];  // Short description
typedef unsigned      Price;             // Price in cents

typedef struct _product_s {
    Description description;
    Name  name;
    Key   id;
    Price price;
    short quantity;
} Product;


#endif // _PRODUCT_H
