#include "../include/graph.h"

struct _bfs_node_s {
    struct _bfs_node_s *next;
    size_t id;
};

struct _bfs_queue_s {
    struct _bfs_node_s *head;
    struct _bfs_node_s *tail;
};

void bfs_enqueue(struct _bfs_queue_s *queue, size_t id) {
    struct _bfs_node_s* new = (struct _bfs_node_s*) malloc(sizeof(struct _bfs_node_s));
    
    new->id = id;
    new->next = NULL;
    
    if(queue->head == NULL) {
        queue->head = new;
        queue->tail = new;
        return;
    }
    
    queue->tail->next = new;
}
size_t bfs_dequeue(struct _bfs_queue_s *queue) {
    struct _bfs_node_s *aux = queue->head;
    size_t ret = aux->id;

    queue->head = aux->next;

    free(aux);
    
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
    struct _edge_s *edge_travel;
    size_t destiny;
    
    // Vetor que contém as distâncias do âncora para todos os outros
    unsigned *dists = (unsigned*) malloc(sizeof(unsigned) * vertex_count); 
    for(size_t i = 0; i < vertex_count; i++) dists[i] = (unsigned) -1;
    
    // Vetor que contém as cores de cada vértice
    uint8_t *colours = calloc(vertex_count, sizeof(uint8_t));

    // Fila utilizada na busca em largura
    struct _bfs_queue_s queue = { .head = NULL,
                                  .tail = NULL };
    
    size_t visited;
    size_t dist = 0;
    
    bfs_enqueue(&queue, aux->id);
    colours[aux->id] = GRAY;
    dists[aux->id] = dist;
    
    dist++;
    
    while(queue.head) {
        edge_travel = (vertexes[queue.head->id]).head;
        
        while(edge_travel) {
            destiny = edge_travel->destiny;

            printf("visitarei %lu de cor %d\n", destiny, colours[destiny]);
            
            if(colours[destiny] == WHITE) {
                bfs_enqueue(&queue, destiny);
                colours[destiny] = GRAY;
                dists[destiny] = dist;
            }
            
            edge_travel = edge_travel->next;
        }
        visited = bfs_dequeue(&queue);
        colours[visited] = BLACK;
        dist++;
        printf("Visted: %lu\nDistance from anchor: %u\n\n", visited, dists[visited]);
    }
    
    free(dists);
    free(colours);
}

void dfs(Graph this) {
    
}

// TODO (!) carece de testes
void add_vertex(Graph this) {
    struct _vertex_s new;
    new.id = this->__vertex_count;
    new.head = NULL;

    this->__vertex_count++;
    
    this->__vertexes = realloc(this->__vertexes, this->__vertex_count * sizeof(struct _vertex_s));
    ((struct _vertex_s*) (this->__vertexes))[new.id] = new;
}

// TODO (!) carece de testes
void add_edge(Graph this, size_t id_a, size_t id_b) {
    struct _vertex_s *vertexes = this->__vertexes;
    
    struct _vertex_s *vertex_a = &(vertexes[id_a]);
    struct _vertex_s *vertex_b = &(vertexes[id_b]);

    struct _edge_s *aux = vertex_a->head;
    while (aux)
    {
        if (aux->destiny == id_b) return;
        aux = aux->next;
    }
    
    struct _edge_s *new_a = (struct _edge_s*) malloc(sizeof(struct _edge_s));
    new_a->destiny = id_b;
    new_a->next = vertex_a->head;
    vertex_a->head = new_a;
    
    struct _edge_s *new_b = (struct _edge_s*) malloc(sizeof(struct _edge_s));
    new_b->destiny = id_a;
    new_b->next = vertex_b->head;
    vertex_b->head = new_b;
    
}

void print_graph(Graph this) {
    if (this == NULL || this->__vertexes == NULL) {
        printf("Graph is empty!\n");
        return;
    }

    struct _vertex_s *vertexes = this->__vertexes;
    size_t vertex_count = this->__vertex_count;

    printf("Graph with %lu vertices:\n", vertex_count);
    
    for (size_t i = 0; i < vertex_count; i++) {
        struct _vertex_s vertex = vertexes[i];
        printf("Vertex %lu: ", vertex.id);
        
        struct _edge_s *edge = vertex.head;
        if (edge == NULL) {
            printf("no connections");
        } else {
            while (edge != NULL) {
                printf("%lu", edge->destiny);
                edge = edge->next;
                if (edge != NULL) {
                    printf(" -> ");
                }
            }
        }
        printf("\n");
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
    new->print = print_graph;
    return new;
}
