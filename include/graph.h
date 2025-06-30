#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
    struct _vertex_s *__vertexes;
    size_t __vertex_count;
    
// Operações
//  i. Operações que modificam o grafo
    void (*add_vertex)(Graph); // Cria um vértice
    void (*add_edge)(Graph, size_t id_a, size_t id_b); // Conecta dois vértices, i.e., cria uma aresta (função Ψ(G), i.e., Psi(G))

//  ii. Operações que não modificam o grafo
    void (*bfs)(Graph);
    void (*dfs)(Graph);
};

Graph new_graph() {
    Graph new = (Graph) malloc(sizeof(struct _graph_s));
    new->__vertexes = NULL;
    new->__vertex_count = 0;
    return new;
}

void add_vertex(Graph this) {
    struct _vertex_s new;
    new.id = this->__vertex_count;
    new.head = NULL;

    this->__vertexes = realloc(this->__vertexes, ++(this->__vertex_count));
    this->__vertexes[new.id] = new;
}

// ainda tô fazendo essa função
void add_edge(Graph this, size_t id_a, size_t id_b) {
    struct _vertex_s *vertex_a = &(this->__vertexes[id_a]);
    struct _vertex_s *vertex_b = &(this->__vertexes[id_b]);

    struct _edge_s *aux_a = vertex_a->head;
    struct _edge_s *aux_b = vertex_b->head;

    struct _edge_s *new_a;
    struct _edge_s *new_b;

    if(aux_a) {
        while(aux_a->next) {
            if(aux_a->destiny == id_b) return;
            aux_a = aux_a->next;
        }
    }

    new_a = (struct _edge_s*) malloc(sizeof(struct _edge_s));
    new_a->destiny = id_b;
    new_a->next = NULL;
    
}

#endif // _GRAPH_H
