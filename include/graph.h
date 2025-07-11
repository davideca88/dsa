#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define WHITE 0
#define GRAY  1
#define BLACK 2

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
    void *__path;
    void *__vertexes;
    size_t __vertex_count;
    float min_degree;
    float current_degree;

// Operações
//  i. Operações que modificam o grafo
    void (*gen_graph)(Graph, size_t n, float percent, bool cycle);

//  ii. Operações que não modificam o grafo
    void (*bfs)(Graph, size_t anchor);
    // void (*dfs)(Graph);
    void (*print)(Graph);
    void (*print2)(Graph, size_t archor, char search);
    void (*print3)(Graph, size_t archor);
};

Graph new_graph();

#endif // _GRAPH_H
