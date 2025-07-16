#include "include/graph.h"
#include "include/benchmark.h"

//EXEMPLO 6: Benchmark entre DFS e BFS

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
make run prog=ex6

outros comandos:
make run-all (executa todos)
make clean (limpa todos txt e executáveis)

*/

int main(){
    srand(time(NULL));

    bm_graph("ex6.txt");

    return 0;
}