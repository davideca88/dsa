#include "include/graph.h"

int main() {
    
    srand(time(NULL));

    
    Graph g = new_graph();

    
    size_t num_vertices = 15;
    g->gen_graph(g, num_vertices, 30.0f, true);
    
    printf("Estrutura do Grafo Gerado:\n");
    g->show_graph(g);
    printf("\n-------------------------------------\n");


    size_t inicio = 0;
    size_t fim = num_vertices - 1;

    
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); 

    // Chama a função de todos os caminhos
    g->find_all_paths(g, inicio, fim);

    end_time = clock();


    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n-------------------------------------\n");
    printf("Tempo de execução da busca: %f segundos\n", cpu_time_used);
    
    return 0;
}
