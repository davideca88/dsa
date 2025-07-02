#include "../include/graph.h"

struct _bfs_node_s {
    struct _bfs_node_s *next;
    size_t id;
    unsigned dist;
//    uint8_t colour;
};

struct _bfs_queue_s {
    struct _bfs_node_s *head;
    struct _bfs_node_s *tail;
};

void bfs_enqueue(struct _bfs_queue_s *queue, size_t id, unsigned dist) {
    struct _bfs_node_s* new = (struct _bfs_node_s*) malloc(sizeof(struct _bfs_node_s));
    
    new->id = id;
    new->dist = dist;
//    new->colour = colour;
    new->next = NULL;
    
    if(queue->head == NULL) {
        queue->head = new;
        queue->tail = new;
        return;
    }
    
    queue->tail->next = new;
}
size_t bfs_dequeue(struct _bfs_queue_s *queue) {
    size_t ret = queue->tail->id;
    struct _bfs_node_s *aux = queue->head;
    
    while(aux->next) aux = aux->next;

    free(aux->next);
    aux->next = NULL;
    
    return ret;
}

// fazendo
void bfs(Graph this) {
    struct _vertex_s *vertexes = this->__vertexes;
    size_t vertex_count = this->__vertex_count;
    
    if(vertex_count == 0) return;
    
    // Vértice auxiliar que percorrerá o grafo. O primeiro eleito é o chamado
    // "âncora" (a busca começa a partir dele) e sempre será o primeiro elemento
    // do vetor de vértices (pois é o único garantido em um grafo não vazio)
    struct _vertex_s *aux = vertexes;

    // Ponteiro para percorrer a lista de adjacência
    struct _edge_s *travel;
    
    // Vetor que contém as distâncias do âncora para todos os outros
    unsigned *dist = (unsigned*) malloc(sizeof(unsigned) * vertex_count);
    
    // Vetor que contém as cores de cada vértice
    uint8_t *colours = calloc(vertex_count, sizeof(uint8_t));

    // Fila utilizada na busca em largura
    struct _bfs_queue_s queue = { .head = NULL,
                                  .tail = NULL };
    
    bfs_enqueue(&queue, aux->id, 0);
    colours[aux->id] = GRAY;

    size_t dist_inc = 1;
    
    while(queue.head) {
        travel = aux->head;
        while(travel) {
             bfs_enqueue(&queue, travel->destiny, dist_inc++);
             colours[travel->destiny] = GRAY;
             travel = travel->next;
        }
        colours[bfs_dequeue(&queue)] = BLACK;
    }
    
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
