#include "../include/arena.h"

#include <stdlib.h>

#include "../include/utils.h"

// isso tá fei demais
#define _CAN_ARENA_ALLOC(arena_ptr, size) \
    (&((ar->alloc_ptr)[ar->block_size - 1]) - &((ar->alloc_ptr)[size]) >= 0)

struct _arena_block *_arena_create_block(size_t block_size)
{    
    struct _arena_block *new = \
                    (struct _arena_block*) malloc(sizeof(struct _arena_block));

    check_allocation(new, "Can\'t allocate block");
    
    u8 *buffer = (u8*) malloc(block_size);

    check_allocation(buffer, "Can\'t allocate block buffer");
    
    new->buffer = buffer;
    new->node = (struct list_node) {.next = &(new->node), .prev = &(new->node)};
    new->prev_end = NULL;
    
    return new;
}

void _arena_grow(struct arena *ar)
{
    struct _arena_block *block = _arena_create_block(ar->block_size);
    
    list_add_tail(&(ar->arena_head), &(block->node));
    
    block->prev_end = ar->alloc_ptr;

    ar->alloc_ptr = block->buffer;
}

/*
 * arena_init - inicializa uma arena com bloco de tamanho @block_size
 *
 * @block_size:     tamanho do bloco (em bytes)
 */
struct arena arena_init(size_t block_size)
{    
    LIST_HEAD(arena_head);
    u8 *ptr;
    size_t aligned_block_size;
    struct _arena_block *initial_block;

    aligned_block_size = ALIGN_TO(block_size, ARENA_ALIGNMENT);

    initial_block = _arena_create_block(aligned_block_size);
    
    list_head_init(&arena_head);
    list_add_tail(&arena_head, &(initial_block->node));
 
    return (struct arena) { .block_size = aligned_block_size,
                            .arena_head = arena_head,
                            .current_block = initial_block,
                            .alloc_ptr = initial_block->buffer };
}

void arena_rewind(struct arena *ar)
{
    ar->current_block = 
                LIST_ENTRY(ar->arena_head.current, struct _arena_block, node);
    ar->alloc_ptr = ar->current_block->buffer;
}

void arena_destroy(struct arena *ar)
{
    struct list_node *aux = ar->arena_head.current, 
                     *curr = aux,
                     *next;
    
    do {
        next = aux->next;
        free(aux);
    } while(aux != curr);

    ar->arena_head = (struct list_head) { .current = NULL };
}


void *arena_alloc(struct arena *ar, size_t size)
{
    size = ALIGN_TO(size, ARENA_ALIGNMENT);
    
    struct _arena_block *curr = ar->current_block;
    void *ptr = ar->alloc_ptr;
    
    struct list_node *aux;
    
    if(size > ar->block_size) {
        fprintf(stderr, "Can\'t use this arena. Block size is too small");
    }
    
    if(_CAN_ARENA_ALLOC(ar, size)) {
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
