/*
 *
 * Cabeçalho que contém uma API de listas duplamente encadeadas
 *
 * Essa implementação de lista duplamente encadeada é de natureza circular.
 * A principal vantagem disso é que se quisermos acessar a calda da lista, basta
 * apenas ir para o anterior do elemento cabeça (i.e., o primeiro elemento da
 * lista, sem considerar o `marcador`)
 *
 */
#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>

#include "macros.h"

struct list_node {
    struct list_node *prev;
    struct list_node *next;
};

struct list_head {
    struct list_node *current;
};

/*
 * LIST_HEAD - cria uma cabeça — marcador — de lista
 *
 * @name:       nome da cabeça
 *
 * A cabeça não possui dados além de dados da lista. Ela atua apenas como
 * marcador do início da lista. Por isso, não faz sentido usar operações de 
 * remoção nesse nó.
 */
#define LIST_HEAD(name) \
    struct list_head name

/*
 * LIST_ENTRY - acha o endereço da struct (ou typedef)* instanciada que contém o nó
 * 
 * @ptr:        ponteiro do nó conhecido
 * @type:       struct (*) que contém o nó
 * @name:       nome da variável do tipo struct llist_node* dentro da struct (*)
 */
#define LIST_ENTRY(ptr, type, name) \
    CONTAINER_OF(ptr, type, name)

/*
 * LLIST_FOR_EACH - itera sobre toda a lista
 *
 * @head:       cabeça da lista
 * @pos:        elemento que será iterado (criado e destruído localmente)
 *
 * Essa provavelmente não é a melhor mandeira de se fazer isso, mas foi a única
 * que eu consegui pensar
 */
#define LIST_FOR_EACH(head, pos) \
    for(struct list_node *pos = head.current, *marker = NULL; pos != marker; \
                                        pos = pos->next, marker = head.current)

/*
 * list_head_init - inicializa a cabeça da lista
 *
 * @head:       cabeça da lista
 */
static inline void list_head_init(struct list_head *head)
{
    head->current = NULL;
}


/*
 * list_is_empty - verifica se a lista está vazia
 *
 * @head:       cabeça da lista
 */
static inline int list_is_empty(struct list_head *head)
{
    return head->current == NULL;
}

/*
 * list_is_head - verifica se @node é o elemento cabeça atual (current) da lista
 *
 * @head:       cabeça da lista
 * @node:       nó a ser verificado
 */
static inline int list_is_head(struct list_head *head, struct list_node *node)
{
    return head->current == node;
}

/*
 * list_is_tail - verifica se @node é o elemento calda atual (current) da lista
 *
 * @head:       cabeça da lista
 * @node:       nó a ser verificado
 */
static inline int list_is_tail(struct list_head *head, struct list_node *node)
{
    return head->current->prev == node;
}

/*
 *  _list_add - adiciona um nó entre dois outros nós previamente encadeados
 *
 *  @new:       novo nó
 *  @prev:      nó que será anterior à @new
 *  @next:      nó que será posterior à @new
 *
 *  O uso primário dessa função é como func. auxiliar para as operações dentro
 *  deste cabeçalho. Mas nada impede o usuário de usá-la fora daqui (desde que
 *  ele saiba o que está fazendo)
 */
static inline void _list_add(struct list_node *new, struct list_node *prev, \
                                                        struct list_node *next)
{
    new->prev = prev;
    prev->next = new;

    new->next = next;
    next->prev = new;
}

/*
 * _list_remove - remove um nó de uma lista fazendo seu anterior e o seu próximo
 * apontarem um para o outros
 *
 * @rem:        nó que será removido
 *
 * A função retorna se foi possível remover o nó da lista. O único caso em que
 * não é possível é quando se trata de uma LISTA UNITÁRIA
 */
static inline int _list_remove(struct list_node *rem)
{
    if(rem->next != rem) {
        rem->prev->next = rem->next;
        rem->next->prev = rem->prev;
    }

    return rem->next != rem;
}

/*
 * list_insert_pos - insere uma sublista previamente encadeada em outra lista
 * também previamente encadeada
 *
 * @pos:        elemento `posição`
 * @new_head:   elemento cabeça da sublista
 * @new_tail:   calda da sublista
 *
 * @new_head tomará a posição de @pos dentro da lista original após a inserção
 */
static inline void list_insert_pos(struct list_node *pos, \
                        struct list_node *new_head, struct list_node *new_tail)
{
    struct list_node *pos_prev = pos->prev;
    
    pos_prev->next = new_head;
    new_head->prev = pos_prev;

    new_tail->next = pos;
    pos->prev = new_tail;
    
}

/*
 *  list_insert_tail - insere uma sublista na calda de uma lista
 *
 * @head:       cabeça da lista que sofrerá a inserção
 * @new_head:   elemento cabeça da sublista
 * @new_tail:   calda da sublista
 */
static inline void list_insert_tail(struct list_head *head, \
                        struct list_node *new_head, struct list_node *new_tail)
{
    
    if(list_is_empty(head)) {
        head->current = new_head;
        return;
    }

    list_insert_pos(head->current->prev, new_head, new_tail);
}

/*
 *  list_insert_head - insere uma sublista na cabeça de uma lista
 *
 * @head:       cabeça da lista que sofrerá a inserção
 * @new_head:   elemento cabeça da sublista
 * @new_tail:   calda da sublista
 */
static inline void list_insert_head(struct list_head *head, \
                        struct list_node *new_head, struct list_node *new_tail)
{
    list_insert_tail(head, new_head, new_tail);
    head->current = new_head;
}

/*
 * list_add_tail - adiciona um único elemento à calda de uma lista
 *
 * @head:       cabeça da lista
 * @new:        elemento inserido
 */
static inline void list_add_tail(struct list_head *head, struct list_node *new)
{

    if(list_is_empty(head)) {
        new->next = new->prev = new;
        head->current = new;
        return;
    }

    _list_add(new, head->current->prev, head->current);
}

/*
 * list_add_head - adiciona um único elemento à cabeça de uma lista
 *
 * @head:       cabeça da lista
 * @new:        elemento inserido
 */
static inline void list_add_head(struct list_head *head, struct list_node *new)
{
    list_add_tail(head, new); 
    head->current = new;
}

/*
 * list_replace - substitui um elemento por outro dentro de uma lista
 *
 * @old:        elemento antigo
 * @new:        elemento que substituirá @old
 */
static inline void list_replace(struct list_node *old, struct list_node *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

/*
 * list_remove_tail - remove a calda da lista
 *
 * @head:       cabeça da lista
 */
static inline struct list_node *list_remove_tail(struct list_head *head)
{
    struct list_node *tail = head->current->prev;

    if(!_list_remove(tail)) {
        head->current = NULL;
        return NULL;
    }

    return tail;
}

/*
 * list_remove_head - remove a cabeça da lista
 *
 * @head:       cabeça da lista
 */
static inline struct list_node *list_remove_head(struct list_head *head)
{
    struct list_node *current = head->current;
    
    head->current = current->next;

    if(!_list_remove(current)) {
        head->current = NULL;
        return NULL;
    }

    return current;
}

/*
 * list_rotate_left - rotaciona a lista para a esquerda
 *
 * @head:       cabeça da lista
 */
static inline void list_rotate_left(struct list_head *head)
{
    head->current = head->current->next;
}

/*
 * list_rotate_right - rotaciona a lista para a direita
 *
 * @head:       acho que você já entendeu
 */
static inline void list_rotate_right(struct list_head *head)
{
    head->current = head->current->prev;
}

#endif // _LIST_H
