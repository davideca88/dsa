/*
 *
 * Cabeçalho com funções de propósito geral amplamente usadas
 *
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>

/*
 * check_allocation - checa se uma syscall de alocação de memória falhou
 *
 * @ptr:        retorno da função — syscall — de alocação
 * @err_msg:    mensagem de erro personalizada (opcional)
 *
 * Se a alocação falhar, encerrará o programa imediatamente e exibirá uma
 * mensagem em stderr. No caso de não oferecer mensagem de erro, preencher com
 * NULL
 */
static inline void check_allocation(void *ptr, const char* err_msg) {
    if(ptr == NULL) { 
        perror(err_msg ? err_msg : "Heap failed");
        exit(EXIT_FAILURE);
    }
}

#endif // _UTILS_H
