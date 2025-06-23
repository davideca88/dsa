#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Cada aresta é uma lista encadeada, onde cada elemento da lista é um destino desse nó
// obs.: Arestas são específicas de cada nó, i.e., uma  conexão necessita  que ambos os
// vértices  tenham  conexões mútuas, i.e., uma  que "vai" e outra que  "volta" (onde a 
// que "vai" está ma lista do nó "A" e a que "volta" na lista do nó "B")
struct _edge_s {
    size_t destiny; // O destino é um índice no array de vértices
    struct _edge_s *next;
};

struct _vertex_s {
    struct _edge_s *head;
    uint8_t state;
};

typedef struct _graph_s* Graph;
struct _graph_s {
    struct _vertex_s *vertexes;
    size_t _vertex_count;
};

Graph new_graph() {
    Graph new = (Graph) malloc(sizeof(struct _graph_s));
    new->vertexes = NULL;
    new->_vertex_count = 0;
    return new;
}

#endif // _GRAPH_H
