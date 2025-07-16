#include "include/graph.h"

//EXEMPLO 3: Busca em Profundidade (DFS)

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
gcc ex3.c lib/*.o -o ex3 -lm
./ex3 > out3.txt
*/

int main(){
    srand(time(NULL));

    Graph g1 = new_graph();
    Graph g2 = new_graph();
    Graph g3 = new_graph();
    Graph g4 = new_graph();
    Graph g5 = new_graph();
    Graph g6 = new_graph();

    g1->gen_graph(g1, 10, 100, true);
    g2->gen_graph(g2, 10, 50, true);

    g3->gen_graph(g3, 50, 100, true);
    g4->gen_graph(g4, 50, 50, true);

    g5->gen_graph(g5, 100, 40, false);
    g6->gen_graph(g6, 75, 40, false);

    printf("EXEMPLO 1: DFS EM GRAFOS COM CICLO:\n");
    printf("\n--------GRAFO 1--------\n");
    g1->show_graph(g1, true);
    printf("\n--------DFS--------\n");
    g1->print_graph(g1, 0, DFS);
    
    printf("\n--------GRAFO 2--------\n");
    g2->show_graph(g2, true);
    printf("\n--------DFS--------\n");
    g2->print_graph(g2, 5, DFS);

    printf("\n--------GRAFO 3--------\n");
    g3->show_graph(g3, false);
    printf("\n--------DFS--------\n");
    g3->print_graph(g3, 32, DFS);

    printf("\n--------GRAFO 4--------\n");
    g4->show_graph(g4, false);
    printf("\n--------DFS--------\n");
    g4->print_graph(g4, 22, DFS);

    printf("\n###########################################\n");

    printf("\nEXEMPLO 2: DFS EM GRAFOS SEM CICLO:\n");
    printf("\n--------GRAFO 5--------\n");
    g5->show_graph(g5, false);
    printf("\n--------DFS--------\n");
    g5->print_graph(g5, 62, DFS);

    printf("\n--------GRAFO 6--------\n");
    g6->show_graph(g6, false);
    printf("\n--------DFS--------\n");
    g6->print_graph(g6, 12, DFS);

    return 0;
}