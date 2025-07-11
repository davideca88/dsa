#include "../include/graph.h"

// Essa função macro só pega a cor e transforma uma string
// Propósito majoritário p/ debug
#define COLOUR_STRING(c) c == WHITE ? "WHITE" : (c == GRAY ? "GRAY" : "BLACK")

static inline bool allocation_failed(void *ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Allocation has failed =(\n");
        return true;
    }
    return false;
}

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
    
    if(allocation_failed(new))
        return;
    
    new->id = id;
    new->next = NULL;
    
    if(queue->head == NULL) {
        queue->head = new;
        queue->tail = new;
        return;
    }
    
    queue->tail->next = new;
    queue->tail = new;
}

size_t bfs_dequeue(struct _bfs_queue_s *queue) {
    struct _bfs_node_s *aux = queue->head;
    size_t ret;
    
    if(aux == NULL)
        return (size_t) -1;
    
    ret = aux->id;

    queue->head = aux->next;

    if(queue->head == NULL)
        queue->tail = NULL;

    free(aux);
    
    return ret;
}

// fazendo
void bfs(Graph this, size_t anchor) {
    struct _vertex_s *vertexes = this->__vertexes;
    size_t vertex_count = this->__vertex_count;
    
    size_t *path = this->__path;
    // Iterador de path utilizado na construção de __path[]
    size_t path_i = 0;
    
    if(anchor >= vertex_count)
        return;
    
    // Seleciona vértice âncora, i.e., recebe seu endereço
    struct _vertex_s *aux = &(vertexes[anchor]);

    // Ponteiro para percorrer a lista de adjacência
    struct _edge_s *travel;
    size_t destiny;
    
    // Vetor que contém as distâncias do âncora para todos os outros
    unsigned *dists = (unsigned*) malloc(sizeof(unsigned) * vertex_count);

    if(allocation_failed(dists))
        return;
    
    for(size_t i = 0; i < vertex_count; i++) dists[i] = (unsigned) -1;
    
    // Vetor que contém as cores de cada vértice
    uint8_t *colours = calloc(vertex_count, sizeof(uint8_t));

    if(allocation_failed(colours))
        return;

    // Fila utilizada na busca em largura
    struct _bfs_queue_s queue = { .head = NULL,
                                  .tail = NULL };
    size_t queue_head_id;
    size_t visited;
     
    bfs_enqueue(&queue, aux->id);
    colours[aux->id] = GRAY;
    dists[aux->id] = 0;

    // Nesse ponto path_i = 0, então definimos __path[0] = anchor,
    // pois o caminho percorrido começa no vértice âncora
    path[path_i] = anchor;
    path_i++;
    
    while(queue.head) {
        queue_head_id = queue.head->id;
        travel = (vertexes[queue_head_id]).head;

        
        while(travel) {
            destiny = travel->destiny; 
            
            if(colours[destiny] == WHITE) {
                bfs_enqueue(&queue, destiny);
                colours[destiny] = GRAY;
                dists[destiny] = dists[queue_head_id] + 1;

                path[path_i] = destiny;
                path_i++;
            }

            travel = travel->next;
        }

        visited = bfs_dequeue(&queue);
        colours[visited] = BLACK;
    }
    
    free(dists);
    free(colours);
}

void dfs(Graph this) {
    
}


void add_vertex(Graph this) {
    struct _vertex_s new;
    new.id = this->__vertex_count;
    new.head = NULL;

    size_t **path = (size_t**) &(this->__path);

    this->__vertex_count++;
    
    this->__vertexes = realloc(this->__vertexes, \
            this->__vertex_count * (sizeof(struct _vertex_s) + sizeof(size_t)));

    *path = (size_t*) &(this->__vertexes[this->__vertex_count]);

    *path[this->__vertex_count - 1] = (size_t) -1;
    
    ((struct _vertex_s*) (this->__vertexes))[new.id] = new;
}


bool add_edge(Graph this, size_t id_a, size_t id_b) {
    struct _vertex_s *vertexes = this->__vertexes;
    
    struct _vertex_s *vertex_a = &(vertexes[id_a]);
    struct _vertex_s *vertex_b = &(vertexes[id_b]);

    struct _edge_s *new_a;
    struct _edge_s *new_b;

    struct _edge_s *aux = vertex_a->head;
    
    while(aux) {
        if (aux->destiny == id_b)
            return false;
        aux = aux->next;
    }
    
    new_a = (struct _edge_s*) malloc(sizeof(struct _edge_s));

    if(allocation_failed(new_a))
        return false;
    
    new_a->destiny = id_b;
    new_a->next = vertex_a->head;
    vertex_a->head = new_a;
    
    new_b = (struct _edge_s*) malloc(sizeof(struct _edge_s));

    if(allocation_failed(new_b))
        return false;
    
    new_b->destiny = id_a;
    new_b->next = vertex_b->head;
    vertex_b->head = new_b;

    return true;
}

/**
 * Função: gen_graph
 * ---------
 * Gera um grafo não direcionado e conexo com `n` vértices e grau de conectividade
 * aproximado de `percent` (0 a 100).
 *
 * Parâmetros:
 *  - this: ponteiro para o grafo
 *  - n: número de vértices
 *  - percent: porcentagem desejada de conectividade
 *  - cycle: caso seja 0, garante que o grafo não tenha ciclos
 * 
 * Comportamento:
 *  - Cria os vértices
 *  - Garante conexidade com uma árvore de n-1 arestas
 *  - Adiciona arestas aleatórias até atingir o grau de conectividade
 *  - Calcula e armazena a conectividade mínima (min_degree) e atual (current_degree)
 */

void gen_graph(Graph this, size_t n, float percent, bool cycle) {
    if (percent < 0 || percent > 100) {
        printf("Error: invalid percentage\n");
        return;
    }

    for (size_t i = 0; i < n; i++) {
        add_vertex(this);
    }

    for (size_t i = 1; i < n; i++) {
        size_t parent = rand() % i;
        add_edge(this, i, parent);
    }

    size_t max_edges = (n * (n - 1)) / 2;
    size_t target_edges = (size_t) ceil((percent / 100.0) * max_edges);

    if (cycle && target_edges <= n-1)target_edges = n;
    else if (!cycle)target_edges = n-1;
    

    size_t current_edges = n - 1;
    while (current_edges < target_edges) {
        size_t id_a = rand() % n;
        size_t id_b = rand() % n;

        if (id_a != id_b && add_edge(this, id_a, id_b)) current_edges++;
    }
    this->current_degree = ((float)current_edges/max_edges)*100;
    this->min_degree = ((float)(n-1)/max_edges)*100;
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

    if(allocation_failed(new))
        return NULL;
    
    new->__vertexes = NULL;
    new->__vertex_count = 0;
    new->current_degree = 0;
    new->min_degree = 0;
    
    new->gen_graph = gen_graph;

    new->bfs = bfs;
    new->dfs = dfs;
    new->print = print_graph;
    return new;
}
