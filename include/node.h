#ifndef _NODE_H
#define _NODE_H

// Nó padrão para árvores binárias
typedef struct _node_s {
    struct _node_s* l;
    struct _node_s* r;
    int data;
} Node;

#endif // _NODE_H
