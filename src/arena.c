#include "../include/arena.h"

#include <stdlib.h>

#include "../include/utils.h"

/*
 * arena_init - inicializa uma arena com bloco de tamanho @block_size
 *
 * @block_size:     tamanho do bloco (em bytes)
 */
struct arena arena_init(size_t block_size) {
    
    LLIST_HEAD(arena_head);
    u8 *ptr;

    arena_head = llist_head_init();

    ptr = (u8*) malloc(block_size);

    check_allocation(ptr, "Can\'t allocate arena initial block");
 
    struct _arena_block *inital_block = \
        (struct _arena_block*) malloc(sizeof(struct _arena_block));

    inital_block->ptr = ptr;
    llist_add(&arena_head, &(inital_block->node));
    
    return (struct arena) { .block_size = block_size,
                            .arena_head = arena_head,
                            .used_space = 0,
                            .block_count = 1};
}

void arena_push(struct arena *ar, size_t size) {
    
}
