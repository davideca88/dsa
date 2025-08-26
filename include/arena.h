#ifndef _ARENA_H
#define _ARENA_H

#include <stddef.h>

#include "list.h"
#include "macros.h"
#include "types.h"

#define ARENA_ALIGNMENT 16

// vou precisar da duplamente encadeada

struct _arena_block {
    struct list_node node;
    u8 *prev_end;
    u8 *buffer;
};

struct arena {
    struct list_head arena_head;
    const size_t block_size;
    struct _arena_block *current_block;
    void *alloc_ptr;
};

struct arena arena_init(size_t block_size);

#endif // _ARENA_H
