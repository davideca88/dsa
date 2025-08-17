#ifndef _MACROS_H
#define _MACROS_H

#include <stddef.h>

#ifndef MAX
#define MAX(a, b) (a) > (b) ? (a) : (b)
#endif // MAX

#ifndef MIN
#define MIN(a, b) (a) < (b) ? (a) : (b)
#endif // MIN

/*
 * SIZEOF_MEMBER - retorna o tamanho de um membro de um tipo (ou struct)
 * 
 * @type:       tipo genérico
 * @member:     membro do tipo type
 */
#define SIZEOF_MEMBER(type, member) \
    (size_t) sizeof( ((type*) 0)->member)

/*
 * CONTAINER_OF - acha o endereço de uma estrutura dado um ponteiro para um
 *                membro
 * 
 * @ptr:        ponteiro para o membro
 * @type:       tipo (struct ou typedef)
 * @member:     membro o qual sabemos o ponteiro
 *
 * (!) Aviso: essa macro não tem type checking e removerá qualquer qualificador
 * const de @ptr.
 */
#define CONTAINER_OF(ptr, type, member) \
    (type*) ((char *) (ptr) - offsetof((type), (member)))

#endif // _MACROS_H
