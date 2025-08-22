#include "../include/arena.h"

#include <stdlib.h>

#include "../include/utils.h"

/*
 * arena_init - inicializa uma arena com bloco de tamanho @block_size
 *
 * @block_size:     tamanho do bloco (em bytes)
 */
struct arena arena_init(size_t block_size)
{    
    LIST_HEAD(arena_head);
    u8 *ptr;

    list_head_init(&arena_head);

    ptr = (u8*) malloc(block_size);

    check_allocation(ptr, "Can\'t allocate arena initial block");
 
    struct _arena_block *inital_block = \
        (struct _arena_block*) malloc(sizeof(struct _arena_block));

    list_add_tail(&arena_head, &(inital_block->node));
    inital_block->buffer = ptr;
    inital_block->prev_end = NULL;
    
    return (struct arena) { .block_size = block_size,
                            .arena_head = arena_head,
                            .current_block = inital_block,
                            .alloc_ptr = inital_block->buffer};
}

void arena_rewind(struct arena *ar)
{
    ar->current_block = 
                LIST_ENTRY(ar->arena_head.current, struct _arena_block, node);
    ar->alloc_ptr = ar->current_block->buffer;
}

void arena_free_all(struct arena *ar)
{
    struct list_node *aux = ar->arena_head.current, 
    *curr = aux, *next;
    
    do {
        next = aux->next;
        free(aux);
    } while(aux != curr);

    ar->arena_head = (struct list_head) { .current = NULL };
}

struct _arena_block *_arena_create_block(size_t block_size)
{
    struct _arena_block *new = \
                    (struct _arena_block*) malloc(sizeof(struct _arena_block));

    check_allocation(new, "Can\'t allocate block");
    
    u8 *buffer = (u8*) malloc(block_size);

    check_allocation(buffer, "Can\'t allocate block buffer");
    
    new->buffer =buffer;
    
    return new;
}

#define _ARENA_CAN_ALLOC(arena_ptr, size) \
    (&((ar->alloc_ptr)[ar->block_size - 1]) - &((ar->alloc_ptr)[size]) >= 0)


void _arena_grow(struct arena *ar)
{
    struct _arena_block *block = _arena_create_block(ar->block_size);
    
    list_add_tail(&(ar->arena_head), &(block->node));
    
    block->prev_end = ar->alloc_ptr;

    ar->alloc_ptr = block->buffer;
}

void *arena_alloc(struct arena *ar, size_t size)
{
    struct _arena_block *curr = ar->current_block;
    void *ptr = ar->alloc_ptr;
    
    struct list_node *aux;
    
    if(size > ar->block_size) {
        fprintf(stderr, "Can\'t use this arena. Block size is too small");
    }
    
    if(_ARENA_CAN_ALLOC(ar, size)) {
        ar->alloc_ptr += size;
        return ptr;
    }

    if(list_is_tail(&(ar->arena_head), &(curr->node))) {
        _arena_grow(ar);
        return ar->alloc_ptr;
    }
    
    ar->current_block =
        LIST_ENTRY(list_node_next(&(curr->node)), struct _arena_block, node);

    ar->alloc_ptr = ar->current_block->buffer;
    
    return ar->alloc_ptr;
}

void arena_push(struct arena *ar, void *buffer, size_t size)
{
    
}

void arena_pop(struct arena *ar, void *buffer, size_t size)
{
    
}
