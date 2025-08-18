#ifndef _ARENA_H
#define _ARENA_H

#include <stddef.h>

#include "llist.h"
#include "types.h"

// vou precisar da duplamente encadeada

struct _arena_block {
    struct llist_node node;
    u8 *ptr;
};

struct arena {
    u16 block_count;
    struct llist_head arena_head;
    const size_t block_size; 
    size_t used_space;
};

struct arena arena_init(size_t block_size);

#endif // _ARENA_H
