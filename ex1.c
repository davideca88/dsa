#include "include/graph.h"

//EXEMPLO 1: Criar grafos conexos com diferentes quantidades de vértices e graus de conectividade

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
gcc ex1.c lib/*.o -o ex1 -lm
./ex1 > out1.txt
*/

int main(){
    srand(time(NULL));

    printf("EXEMPLO 1: CRIANDO UM GRAFO AUTOMATICAMENTE COM PARÂMETROS:\n");
    Graph g1 = new_graph();

    //Cria um grafo com 10 vértices, 50% de conectividade
    g1->gen_graph(g1, 10, 50, true);
    //Mostra toda estrutura do grafo, incluindo as informações gerais
    g1->show_graph(g1, true);

    printf("\n--------------------------------\n");

    //Cria um grafo com 25 vértices, 70% de conectividade
    Graph g2 = new_graph();

    g2->gen_graph(g2, 25, 70, true);
    g2->show_graph(g2, true);

    printf("\n--------------------------------\n");

    //Cria um grafo com 20 vértices, 65% de conectividade
    Graph g3 = new_graph();

    g3->gen_graph(g3, 20, 65, true);
    g3->show_graph(g3, true);

    printf("\n################################\n");

    printf("EXEMPLO 2: CRIANDO UM GRAFO MANUALMENTE:\n");
    Graph g4 = new_graph();

    //Cria um grafo com 4 vértices de 0-3
    g4->add_vertex(g4);
    g4->add_vertex(g4);
    g4->add_vertex(g4);
    g4->add_vertex(g4);

    //Conecta os vértices conforme as instruções do usuário
    g4->add_edge(g4, 0, 1);
    g4->add_edge(g4, 1, 2);
    g4->add_edge(g4, 2, 3);
    g4->add_edge(g4, 3, 0);

    g4->show_graph(g4, true);

    printf("\n--------------------------------\n");

    Graph g5 = new_graph();

    //Cria um grafo com 4 vértices de 0-2
    g5->add_vertex(g5);
    g5->add_vertex(g5);
    g5->add_vertex(g5);

    g5->add_edge(g5, 0, 2);
    g5->add_edge(g5, 1, 2);

    g5->show_graph(g5, true);

    return 0;
}
