#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>

// Nó padrão para árvores binárias
typedef struct _node_s {
    struct _node_s* l;
    struct _node_s* r;
    uint32_t data;
} Node;

#endif // _NODE_H
