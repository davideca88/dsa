/*
 *
 * Cabeçalho com funções de propósito geral amplamente usadas
 *
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * check_allocation - checa se uma syscall de alocação de memória falhou
 *
 * @ptr:        retorno da função — syscall — de alocação 
 *
 * Se a alocação falhar, encerrará o programa imediatamente e exibirá uma
 * mensagem em stderr
 */
static inline void check_allocation(void *ptr) {
    if(ptr == NULL) {
        perror("Heap failed");
        exit(EXIT_FAILURE);
    }
}

#endif // _UTILS_H
