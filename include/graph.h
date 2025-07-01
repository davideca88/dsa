#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Cada aresta é uma lista encadeada, onde cada elemento da lista é um destino desse nó
// obs.: Arestas são específicas de cada nó, i.e., uma  conexão necessita  que ambos os
// vértices  tenham  conexões mútuas, i.e., uma  que "vai" e outra que  "volta" (onde a 
// que "vai" está na lista do nó "A" e a que "volta" na lista do nó "B")
struct _edge_s {
    size_t destiny; // O destino é um índice no array de vértices
    struct _edge_s *next;
};

struct _vertex_s {
    size_t id; // O id é o índice do vértice no array "__vertexes"
    struct _edge_s *head;
};

typedef struct _graph_s* Graph;
struct _graph_s {
// Dados
    void *__vertexes;
    size_t __vertex_count;
    
// Operações
//  i. Operações que modificam o grafo
    void (*add_vertex)(Graph); // Cria um vértice
    void (*add_edge)(Graph, size_t id_a, size_t id_b); // Conecta dois vértices, i.e., cria uma aresta (função Ψ(G), i.e., Psi(G))

//  ii. Operações que não modificam o grafo
    void (*bfs)(Graph);
    void (*dfs)(Graph);
};

#endif // _GRAPH_H
