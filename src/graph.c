#include "../include/graph.h"

// Essa função macro só pega a cor e transforma uma string
// Propósito majoritário p/ debug
#define COLOUR_STRING(c) c == WHITE ? "WHITE" : (c == GRAY ? "GRAY" : "BLACK")

/* Função: allocation_failed
 * Objetivo:
 *   Verificar se uma alocação de memória falhou.
 *
 * Argumento:
 *   ptr - ponteiro retornado por malloc/calloc/realloc.
 *
 * Retorno:
 *   true se a alocação falhou (ptr == NULL), false caso contrário.
 *   Também imprime mensagem de erro padrão para stderr se falhar.
 */

static inline bool allocation_failed(void *ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Allocation has failed =(\n");
        return true;
    }
    return false;
}

//Tipo de função callback usada em DFS para processar cada vértice visitado
typedef void (*_dfs)(
    Graph g, size_t current, size_t parent,
    uint8_t *color, size_t *path, size_t path_len, void *ctx);

//Armazena a sequência de vértices visitados durante a DFS
struct _sequence
{
    size_t *seq;
    size_t idx;
};

//Representa um nó da fila usada na BFS.
struct _bfs_node_s {
    struct _bfs_node_s *next;
    size_t id;
};

//Representa a fila de BFS com ponteiros para início e fim.
struct _bfs_queue_s {
    struct _bfs_node_s *head;
    struct _bfs_node_s *tail;
};

/* Função: bfs_enqueue (Função Auxiliar)
 * Objetivo:
 *   Inserir um novo vértice (id) no final da fila usada na busca em largura (BFS).
 */

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

/* Função: bfs_dequeue (Função Auxiliar)
 * Objetivo:
 *   Remover e retornar o vértice no início da fila usada na busca em largura (BFS).
 */
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

/* Função: bfs
 * Objetivo:
 *   Executar a busca em largura (BFS) a partir de um vértice de origem e registrar
 *   a ordem dos vértices visitados no vetor __path do grafo.
 *
 * Argumentos:
 *   this   - ponteiro para o grafo (Graph).
 *   anchor - índice do vértice de origem da busca.
 *
 * Retorno:
 *   Nenhum (void). Atualiza o vetor __path com a sequência de visita em BFS.
 */
void bfs(Graph this, size_t anchor, bool print_tree) {
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

    if(print_tree) printf("Anchor: %lu\nDistance 0 from anchor:\n%lu", anchor, anchor);

    bool pflag = true; // Flags p/ impressão da árvore
    unsigned pdist;
    
    while(queue.head) {
        queue_head_id = queue.head->id;
        travel = (vertexes[queue_head_id]).head;
            
        while(travel) {
            destiny = travel->destiny;
            
            if(colours[destiny] == WHITE) {
                
                if(pflag && print_tree && pdist != dists[queue_head_id] + 1) {
                    printf("\n\nDistance %u from anchor [%lu]:\n", dists[queue_head_id] + 1, anchor);
                }

                pflag = false;
                
                bfs_enqueue(&queue, destiny);
                colours[destiny] = GRAY;
                dists[destiny] = dists[queue_head_id] + 1;

                path[path_i] = destiny;
                path_i++;

                if(print_tree) {
                    printf("%lu ", destiny);
                    pdist = dists[queue_head_id] + 1;
                }
            }

            travel = travel->next;
        }
        
        pflag = true;
       
        visited = bfs_dequeue(&queue);
        colours[visited] = BLACK;
    }
    
    if(print_tree) putchar('\n');
    
    free(dists);
    free(colours);
}

/* Função: dfs_visit
 * Objetivo:
 *   Executar recursivamente a busca em profundidade (DFS) no grafo, chamando um callback
 *   opcional a cada visita de vértice.
 *
 * Argumentos:
 *   this     - ponteiro para o grafo (Graph).
 *   current  - vértice atualmente sendo visitado.
 *   parent   - vértice anterior na busca.
 *   color    - vetor de cores para controle da visitação (WHITE, GRAY, BLACK).
 *   path     - vetor com o caminho atual da DFS.
 *   path_len - comprimento atual do caminho.
 *   callback - função opcional a ser chamada a cada visita de vértice.
 *   ctx      - ponteiro genérico para contexto adicional, passado ao callback.
 *
 * Retorno:
 *   Nenhum (void). Executa a DFS e atualiza cor, caminho e, se houver, o callback.
 */
static void dfs_visit(Graph this, size_t current, size_t parent,
                              uint8_t *color, size_t *path, size_t path_len,
                              _dfs callback, void *ctx) {
    struct _vertex_s *vertexes = this->__vertexes;
    struct _edge_s *edge = vertexes[current].head;

    color[current] = GRAY;
    path[path_len++] = current;

    if (callback) {
        callback(this, current, parent, color, path, path_len, ctx);
    }

    while (edge) {
        size_t destiny = edge->destiny;
        if (color[destiny] == WHITE) {
            dfs_visit(this, destiny, current, color, path, path_len, callback, ctx);
        }
        edge = edge->next;
    }

    color[current] = BLACK;
}

/* Função: dfs
 * Objetivo:
 *   Iniciar a execução da busca em profundidade (DFS) a partir de um vértice de origem,
 *   utilizando uma função de callback para processar cada visita.
 *
 * Argumentos:
 *   this     - ponteiro para o grafo (Graph).
 *   anchor   - índice do vértice de origem da DFS.
 *   callback - função a ser chamada a cada vértice visitado (pode ser NULL).
 *   ctx      - ponteiro genérico para contexto adicional, passado ao callback.
 *
 * Retorno:
 *   Nenhum (void). Executa a DFS e chama o callback conforme visita os vértices.
 */
void dfs(Graph this, size_t anchor, _dfs callback, void *ctx) {
    size_t n = this->__vertex_count;

    if (anchor >= n) return;

    uint8_t *color = calloc(n, sizeof(uint8_t));
    size_t *path = malloc(n * sizeof(size_t));
    if (allocation_failed(color) || allocation_failed(path)) return;

    dfs_visit(this, anchor, (size_t)-1, color, path, 0, callback, ctx);

    free(color);
    free(path);
}

/* Função: _store_sequence (Função Auxiliar)
 * Objetivo:
 *   Callback usado durante a DFS para armazenar os vértices 
 *   visitados na ordem em que são encontrados.
 */

void _store_sequence(Graph this, size_t current, size_t parent,
                      uint8_t *color, size_t *path, size_t path_len,
                      void *ctx) {
    struct _sequence *sc = ctx;

    if (color[current] == GRAY) {
        sc->seq[sc->idx++] = current;
    }
}

/* Função: dfs_print (Função Auxiliar)
 * Objetivo:
 *   Executar a busca em profundidade (DFS) a partir de um vértice de origem
 *   e armazenar a ordem de visita no vetor __path do grafo.
 */
void dfs_print(Graph this, size_t anchor){
    struct _sequence sc = {
        .seq = calloc(this->__vertex_count, sizeof(size_t)),
        .idx = 0
    };

    dfs(this, anchor, _store_sequence, &sc);

    size_t *path = (size_t*) this->__path;

    for (size_t i = 0; i < sc.idx; i++)
    {
        path[i] = sc.seq[i];
    }

    free(sc.seq);
}

/* Função: detect_cycle (Função Auxiliar)
 * Objetivo:
 *   Detectar ciclos de tamanho ≥ 3 durante a execução de uma DFS.
 */

void detect_cycle(Graph this, size_t current, size_t parent,
                  uint8_t *color, size_t *path, size_t path_len,
                  void *ctx) {
    struct _vertex_s *vertex = this->__vertexes;
    struct _edge_s *edge = vertex[current].head;
    bool *found = ctx;

    if (*found) return;

    while (edge) {
        size_t dest = edge->destiny;

        if (color[dest] == GRAY && dest != parent && path_len >= 3) {
            *found = true;
            return;
        }

        edge = edge->next;
    }
}

/* Função: dfs_cycle
 * Objetivo:
 *   Verificar se o grafo contém algum ciclo de tamanho ≥ 3 usando busca em profundidade (DFS).
 *
 * Argumento:
 *   this - ponteiro para o grafo.
 *
 * Retorno:
 *   Nenhum (void). Imprime no terminal se há ou não ciclo no grafo.
 */

void dfs_cycle(Graph this){
    bool found = false;

    dfs(this, 0, detect_cycle, &found);

    if(found){
        printf("This graph has a cycle!\n");
        return;
    }else{
        printf("There is no cycle in this graph!\n");
        return;
    }
}



/* Função add_vertex
 * Objetivo:
 *   Adicionar um novo vértice ao grafo, realocando a lista de vértices e o vetor de path.
 *
 * Argumento:
 *   this - ponteiro para o grafo (Graph) onde o vértice será inserido.
 *
 * Retorno:
 *   Nenhum (void). Atualiza internamente as estruturas do grafo.
 */
void add_vertex(Graph this) {
    struct _vertex_s new;
    new.id = this->__vertex_count;
    new.head = NULL;
    
    this->__vertex_count++;
    this->__vertexes = realloc(this->__vertexes, this->__vertex_count * sizeof(struct _vertex_s));
    this->__path = realloc(this->__path, this->__vertex_count * sizeof(size_t));

    ((size_t*)this->__path)[this->__vertex_count - 1] = (size_t)-1;
    
    ((struct _vertex_s*) (this->__vertexes))[new.id] = new;
}

/* Função add_edge
 * Objetivo:
 *   Adicionar uma aresta bidirecional entre dois vértices do grafo, caso ainda não exista.
 *
 * Argumentos:
 *   this  - ponteiro para o grafo (Graph).
 *   id_a  - índice do primeiro vértice.
 *   id_b  - índice do segundo vértice.
 *
 * Retorno:
 *   true  - se a aresta foi adicionada com sucesso.
 *   false - se a aresta já existia ou houve falha de alocação.
 */

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
    
    size_t len = this->__vertex_count;
    size_t current_edges = ++this->__edge_count;
    size_t max_edges = (len*(len-1))/2;

    this->__current_degree = ((float)current_edges/max_edges)*100;
    this->__min_degree = ((float)(len-1)/max_edges)*100;

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
 *  - cycle: true - Grafo com ciclos / false - Grafo sem ciclos
 * 
 * Comportamento:
 *  - Cria os vértices
 *  - Garante conexidade com uma árvore de n-1 arestas
 *  - Adiciona arestas aleatórias até atingir o grau de conectividade
 *  - Calcula e armazena a conectividade mínima (__min_degree) e atual (__current_degree)
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
    this->__current_degree = ((float)current_edges/max_edges)*100;
    this->__min_degree = ((float)(n-1)/max_edges)*100;
}

/* Função: show_graph
 * Objetivo: 
 *   Exibir informações gerais e a estrutura completa do grafo, incluindo
 *   grau de conexão, número de vértices e conexões de cada vértice.
 *
 * Argumento:
 *   this - ponteiro para o grafo (Graph) a ser exibido.
 *   all - true - mostra toda estrutura / false - apresenta apenas os dados
 *
 * Retorno:
 *   Nenhum (void). Apenas imprime os dados na saída padrão.
 */

void show_graph(Graph this, bool all) {
    if (this == NULL || this->__vertexes == NULL) {
        printf("Graph is empty!\n");
        return;
    }

    struct _vertex_s *vertexes = this->__vertexes;
    size_t vertex_count = this->__vertex_count;

    printf("GRAPH DATA:\n");
    printf("Current connection degree: %.2f%%\n", this->__current_degree);
    printf("Minimum degree of connection(connected graph): %.2f%%\n", this->__min_degree);
    printf("\nGraph with %lu vertices:\n", vertex_count);
    
    if (all)
    {
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
}

/* Função: print
 * Objetivo:
 *   Executar uma busca (BFS ou DFS) a partir de um vértice de origem e imprimir
 *   a ordem dos vértices visitados.
 *
 * Argumentos:
 *   this   - ponteiro para o grafo (Graph).
 *   anchor - índice do vértice de origem da busca.
 *   search - método de busca a ser usado (BFS ou DFS), definido por SearchMethod.
 *
 * Retorno:
 *   Nenhum (void). Imprime a ordem de visita dos vértices na saída padrão.
 */

void print_graph(Graph this, size_t anchor, SearchMethod search){
    switch (search)
    {
    case BFS:
        bfs(this, anchor, false);
        break;
    
    case DFS:
        dfs_print(this, anchor);
        break;
        
    case BFS_TREE:
        bfs(this, anchor, true);
        return;
    }

    size_t *path = this->__path;
    size_t len = this->__vertex_count;
    const char *_search = (search == 0) ? "BFS" : "DFS";

    printf("Visited Vertexes by %s:", _search);
    for (size_t i = 0; i < len; i++)
    {
        printf("%lu ", path[i]);
    }

    printf("\n");
}

/*
 * Função: _print_found_path (Função Auxiliar)
 *
 * Objetivo: Imprimir um caminho que foi encontrado do início ao fim.
 *
 * Argumentos:
 * path[] - array de caminhos
 * path_len - Tamanho do array
 * 
 * Retorno:
 * Nenhum(void)
 */
static void _print_found_path(size_t path[], size_t path_len) {
    for (size_t i = 0; i < path_len; i++) {
        printf("%zu", path[i]);
        if (i < path_len - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

/*
 * Função: _find_all_paths_util (Função Auxiliar)
 *
 * Objetivo: Encontrar recursivamente todos os caminhos de 'u' para 'd' usando
 * DFS com backtracking.
 *
 * Arrgumentos:
 * this - ponteiro para o grafo
 * u - pseudoinicio
 * d - pseudofim 
 * path - array de caminhos
 * path_len tamanho do array
 */
static void _find_all_paths_util(Graph this, size_t u, size_t d, bool *visited, size_t *path, size_t path_len) {
    // 1. Marca o nó atual como visitado e o adiciona ao array do caminho.
    visited[u] = true;
    path[path_len] = u;
    path_len++;

    // 2. Se o nó atual é o destino, encontramos um caminho.
    if (u == d) {
        _print_found_path(path, path_len);
    } else {
        // 3. Se não for o destino, visite todos os vizinhos recursivamente.
        struct _vertex_s *vertexes = this->__vertexes;
        struct _edge_s *edge = vertexes[u].head;

        while (edge) {
            size_t neighbor = edge->destiny;
            // Prossiga apenas se o vizinho não foi visitado neste caminho para evitar ciclos.
            if (!visited[neighbor]) {
                _find_all_paths_util(this, neighbor, d, visited, path, path_len);
            }
            edge = edge->next;
        }
    }

    // 4. Backtrack: Libera o nó atual do caminho e o desmarca como visitado.
    // Importante....... Isso é para permitir que ele seja parte de outros caminhos.
    visited[u] = false;
}

/*
 * Função: find_all_paths (Implementação do ponteiro de função)
 *
 * Objetivo: Prepara as estruturas necessárias e inicia a busca por todos os caminhos
 * entre um nó de origem (start_node) e um de destino (end_node).
 * 
 * Argumentos:
 * this - ponteiro para o grafo
 * start_node - nó de inicio
 * end_node - nó de fim
 */
void find_all_paths(Graph this, size_t start_node, size_t end_node) {
    size_t n = this->__vertex_count;

    if (start_node >= n || end_node >= n) {
        fprintf(stderr, "Erro: Vértice de início ou fim fora dos limites do grafo.\n");
        return;
    }

    // Array para marcar os nós visitados no caminho ATUAL.
    bool *visited = calloc(n, sizeof(bool));
    // Array para armazenar o caminho ATUAL.
    size_t *path = malloc(n * sizeof(size_t));

    if (allocation_failed(visited) || allocation_failed(path)) {
        free(visited); // É seguro chamar free(NULL)
        free(path);
        return;
    }

    printf("Buscando todos os caminhos de %zu para %zu:\n", start_node, end_node);

    // Inicia a busca recursiva a partir do nó de origem.
    _find_all_paths_util(this, start_node, end_node, visited, path, 0);

    // Libera a memória alocada para esta operação.
    free(visited);
    free(path);
}

/* Função new_graph
 * Objetivo:
 *   Criar e inicializar uma nova estrutura de grafo, atribuindo valores padrão
 *   aos campos de dados e conectando os ponteiros de função.
 *
 * Argumento:
 *   Nenhum.
 *
 * Retorno:
 *   Ponteiro para o novo grafo alocado (Graph), ou NULL se a alocação falhar.
 */
Graph new_graph() {
    Graph new = (Graph) malloc(sizeof(struct _graph_s));

    if(allocation_failed(new))
        return NULL;
    
    new->__path = NULL;
    new->__vertexes = NULL;
    new->__vertex_count = 0;
    new->__edge_count = 0;
    new->__current_degree = 0;
    new->__min_degree = 0;
    
    new->gen_graph = gen_graph;
    new->add_edge = add_edge;
    new->add_vertex = add_vertex;

    new->show_graph = show_graph;
    new->print_graph = print_graph;
    new->dfs_cycle = dfs_cycle;
    //adicionado por mr aed1 
    new->find_all_paths = find_all_paths;

    return new;
}
