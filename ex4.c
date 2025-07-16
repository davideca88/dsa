#include "include/graph.h"

//EXEMPLO 4: Todos os caminhos usando busca em profundidade

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
make run prog=ex4

outros comandos:
make run-all (executa todos)
make clean (limpa todos txt e executáveis)

*/

int main(){
    srand(time(NULL));

    Graph g1 = new_graph();
    Graph g2 = new_graph();
    Graph g3 = new_graph();
    Graph g4 = new_graph();
    Graph g5 = new_graph();
    Graph g6 = new_graph();

    g1->gen_graph(g1, 5, 100, true);
    g2->gen_graph(g2, 5, 50, true);

    g3->gen_graph(g3, 10, 60, true);
    g4->gen_graph(g4, 10, 45, true);

    g5->gen_graph(g5, 7, 50, false);
    g6->gen_graph(g6, 15, 40, false);

    printf("EXEMPLO 1: TODOS OS CAMINHOS EM GRAFOS COM CICLO:\n");
    printf("\n--------GRAFO 1--------\n");
    g1->show_graph(g1, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g1->find_all_paths(g1, 0, 4);
    
    printf("\n--------GRAFO 2--------\n");
    g2->show_graph(g2, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g2->find_all_paths(g2, 0, 4);

    printf("\n--------GRAFO 3--------\n");
    g3->show_graph(g3, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g3->find_all_paths(g3, 7, 9);

    printf("\n--------GRAFO 4--------\n");
    g4->show_graph(g4, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g4->find_all_paths(g4, 0, 3);

    printf("\n###########################################\n");

    printf("\nEXEMPLO 2: TODOS OS CAMINHOS EM GRAFOS SEM CICLO:\n");
    printf("\n--------GRAFO 5--------\n");
    g5->show_graph(g5, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g5->find_all_paths(g5, 0, 6);

    printf("\n--------GRAFO 6--------\n");
    g6->show_graph(g6, true);
    printf("\n--------TODOS OS CAMINHOS--------\n");
    g6->find_all_paths(g6, 0, 14);

    return 0;
}