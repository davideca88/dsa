#include "../include/graph.h"

void bfs(Graph this) {
    if(!this->__vertex_count) return;
}

void dfs(Graph this) {
    
}

// TODO (!) carece de testes
void add_vertex(Graph this) {
    struct _vertex_s new;
    new.id = this->__vertex_count;
    new.head = NULL;

    this->__vertexes = realloc(this->__vertexes, ++(this->__vertex_count));
    ((struct _vertex_s*) (this->__vertexes))[new.id] = new;
}

// TODO (!) carece de testes
void add_edge(Graph this, size_t id_a, size_t id_b) {
    struct _vertex_s *vertex_a = &(this->__vertexes[id_a]);
    struct _vertex_s *vertex_b = &(this->__vertexes[id_b]);

    struct _edge_s *aux_a = vertex_a->head;
    struct _edge_s *aux_b = vertex_b->head;

    struct _edge_s *new_a = (struct _edge_s*) malloc(sizeof(struct _edge_s));
    new_a->destiny = id_b;
    new_a->next = NULL;
    
    struct _edge_s *new_b = (struct _edge_s*) malloc(sizeof(struct _edge_s));
    new_b->destiny = id_a;
    new_b->next = NULL;

    if(!aux_a) {
        vertex_a->head = new_a;
    }
    else {
        while(aux_a->next) {
            if(aux_a->destiny == id_b) {
                free(new_a);
                free(new_b);
                return;
            }
            aux_a = aux_a->next;
        }
        aux_a->next = new_a;
    }

    if(!aux_b) {
        vertex_b->head = new_b;
    }
    else {
        while(aux_b->next) {
            aux_b = aux_b->next;
        }
        aux_b->next = new_b;
    }
    
}

Graph new_graph() {
    Graph new = (Graph) malloc(sizeof(struct _graph_s));
    new->__vertexes = NULL;
    new->__vertex_count = 0;
    
    new->add_vertex = add_vertex;
    new->add_edge = add_edge;

    new->bfs = bfs;
    new->dfs = dfs;
    return new;
}
