#ifndef _PRODUCT_H
#define _PRODUCT_H

typedef unsigned long Key;
typedef char          Name[64];
typedef char          Description[256];
typedef unsigned      Price;

typedef struct _data_s {
    Description description;
    Name  name;
    Key   id;
    Price price;
    short quantity;
} Data;


#endif // _PRODUCT_H
