#include "include/graph.h"

//EXEMPLO 5: Determinar se um dado grafo possui ciclo, usando busca em profundidade.

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
gcc ex5.c lib/*.o -o ex5 -lm
./ex5 > out5.txt
*/

int main(){
    srand(time(NULL));

    Graph g1 = new_graph();
    Graph g2 = new_graph();
    Graph g3 = new_graph();
    Graph g4 = new_graph();
    Graph g5 = new_graph();
    Graph g6 = new_graph();

    g1->gen_graph(g1, 100, 100, rand() % 2);
    g2->gen_graph(g2, 100, 50, rand() % 2);

    g3->gen_graph(g3, 50, 60, rand() % 2);
    g4->gen_graph(g4, 50, 45, rand() % 2);

    g5->gen_graph(g5, 200, 50, rand() % 2);
    g6->gen_graph(g6, 200, 40, rand() % 2);

    printf("EXEMPLO 1: VERIFICAR SE UM GRAFO POSSUI CICLO\n");

    printf("\n--------GRAFO 1--------\n");
    g1->show_graph(g1, false);
    printf("\n--------O GRAFO 1 TEM CICLO?--------\n");
    g1->dfs_cycle(g1);
    
    printf("\n--------GRAFO 2--------\n");
    g2->show_graph(g2, false);
    printf("\n--------O GRAFO 2 TEM CICLO?--------\n");
    g2->dfs_cycle(g2);

    printf("\n--------GRAFO 3--------\n");
    g3->show_graph(g3, false);
    printf("\n--------O GRAFO 3 TEM CICLO?--------\n");
    g3->dfs_cycle(g3);

    printf("\n--------GRAFO 4--------\n");
    g4->show_graph(g4, false);
    printf("\n--------O GRAFO 4 TEM CICLO?--------\n");
    g4->dfs_cycle(g4);

    printf("\n--------GRAFO 5--------\n");
    g5->show_graph(g5, false);
    printf("\n--------O GRAFO 5 TEM CICLO?--------\n");
    g5->dfs_cycle(g5);

    printf("\n--------GRAFO 6--------\n");
    g6->show_graph(g6, false);
    printf("\n--------O GRAFO 6 TEM CICLO?--------\n");
    g6->dfs_cycle(g6);

    return 0;
}