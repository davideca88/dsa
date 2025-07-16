#include "include/graph.h"
#include "include/benchmark.h"

//EXEMPLO 6: Benchmark entre DFS e BFS

/* COMO USAR -> NO TERMINAL, EXECUTE:
make
gcc ex6.c lib/*.o -o ex6 -lm
./ex6
*/

int main(){
    srand(time(NULL));

    bm_graph("ex6.txt");

    return 0;
}