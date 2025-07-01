#include "../include/graph.h"

struct _bfs_node_s {
    struct _bfs_node_s *next;
    size_t id;
    unsigned dist;
    uint8_t colour;
};

struct _bfs_queue_s {
    struct _bfs_node_s *head;
    struct _bfs_node_s *tail;
};

void enqueue(struct _bfs_queue_s* queue, size_t id, unsigned dist, uint8_t colour) {
    struct _bfs_node_s* new = (struct _bfs_node_s*) malloc(sizeof(struct _bfs_node_s));
    
    new->id = id;
    new->dist = dist;
    new->colour = colour;
    new->next = NULL;
    
    if(!queue->head) {
        queue->head = new;
        queue->tail = new;
        return;
    }
    
    queue->tail->next = new;
}
struct _bfs_node_s dequeue();

// fazendo
void bfs(Graph this) {
    if(this->__vertex_count == 0) return;
    
    // Vértice "âncora" (a busca começa a partir dele)
    struct _vertex_s anchor = ((struct _vertex_s*) this->__vertexes)[0];
    
    // Vetor que contém as distâncias do âncora para todos os outros
    unsigned *dist = (unsigned*) malloc(sizeof(unsigned) * this->__vertex_count);
    
    // Vetor que contém as cores de cada vértice
    uint8_t *colours = calloc(this->__vertex_count, sizeof(uint8_t));

    // Fila utilizada na busca em profundidade
    struct _bfs_queue_s queue = { .head = NULL,
                                  .tail = NULL };
    enqueue(&queue, 0, 0, GRAY);
    
    free(dist);
    free(colours);
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
