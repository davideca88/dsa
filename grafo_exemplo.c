#include "include/graph.h"

int main(){
    srand(time(NULL));

    //COMO USAR:
    //NO TERMINAL DIGITE E DÊ ENTER: make
    //DEPOIS: gcc grafo_exemplo.c lib/*.o -o tt1 -lm
    // ./tt1

    printf("EXEMPLO: CRIANDO UM GRAFO AUTOMATICAMENTE COM PARAMETROS:\n");
    Graph g1 = new_graph();

    //cria um grafo com 10 vértices, 50% de conectividade e força a ter ciclo
    g1->gen_graph(g1, 10, 50, true);
    //Mostra toda estrutura do grafo, incluindo as informações gerais
    g1->show_graph(g1);
    //Detecta com DFS se há ciclo, nesse caso há, porque forçamos a ter
    g1->dfs_cycle(g1);
    //Realiza visitas nos vértices do grafo a partir de âncoras; Métodos: BFS e DFS
    g1->print_graph(g1, 5, BFS);
    g1->print_graph(g1, 9, DFS);

    printf("\n");

    printf("EXEMPLO: CRIANDO UM GRAFO MANUALMENTE:\n");
    Graph g2 = new_graph();

    //Cria um grafo com 4 vértices, de 0 a 3;
    g2->add_vertex(g2);
    g2->add_vertex(g2);
    g2->add_vertex(g2);
    g2->add_vertex(g2);

    //Conecta os grafos de modo a serem conexo;
    g2->add_edge(g2, 0, 1);
    g2->add_edge(g2, 1, 2);
    g2->add_edge(g2, 2, 3);

    printf("GRAFO G2 SEM CICLOS:\n");
    g2->show_graph(g2);
    //Inicialmente, nesse ponto, não há ciclos;
    g2->dfs_cycle(g2);

    printf("\n");

    //Entretanto ao adicionar uma nova conexão, um ciclo é formado;
    printf("GRAFO G2 COM CICLOS:\n");
    g2->add_edge(g2, 3, 0);
    g2->add_edge(g2, 2, 0);
    g2->show_graph(g2);
    g2->dfs_cycle(g2);

    return 0;
}