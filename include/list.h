#ifndef _LIST_H
#define _LIST_H

#include <stddef.h>

struct list_node {
    struct list_node *prev;
    struct list_node *next;
};

struct list_head {
    struct list_node *current;
};

#define LIST_HEAD(name) \
    struct list_head name

static inline void list_head_init(struct list_head *head) {
    head->current = NULL;
}

static inline int list_is_empty(struct list_head *head) {
    return head->current == NULL;
}

static inline int list_is_head(struct list_head *head, \
        struct list_node *node) {
    return head->current == node;
}

static inline int list_is_tail(struct list_head *head, 
        struct list_node *node) {
    return head->current->prev == node;
}

static inline void _list_add(struct list_node *new, struct list_node *prev, \
                                                    struct list_node *next) {
    new->prev = prev;
    prev->next = new;

    new->next = next;
    next->prev = new;
}

static inline int _list_remove(struct list_node *rem) {
    if(rem->next != rem) {
        rem->prev->next = rem->next;
        rem->next->prev = rem->prev;
    }

    return rem->next != rem;
}

static inline void list_insert_pos(struct list_node *pos, \
        struct list_node *new_head, struct list_node *new_tail) {
    struct list_node *pos_prev = pos->prev;
    
    pos_prev->next = new_head;
    new_head->prev = pos_prev;

    new_tail->next = pos;
    pos->prev = new_tail;
    
}

static inline void list_insert_tail(struct list_head *head, \
        struct list_node *new_head, struct list_node *new_tail) {
    struct list_node *current = head->current;
    
    if(current) {
        list_insert_pos(current->prev, new_head, new_tail);
        return;
    }
    head->current = new_head;
}

static inline void list_insert_head(struct list_head *head, \
        struct list_node *new_head, struct list_node *new_tail) {
    list_insert_tail(head, new_head, new_tail);
    head->current = new_head;
}

static inline void list_add_tail(struct list_head *head, \
        struct list_node *new) {
    struct list_node *current = head->current;

    if(current) {
        _list_add(new, current->prev, current);
        return;
    }
    head->current = new;
}

static inline void list_add_head(struct list_head *head, \
        struct list_node *new) {
    list_add_tail(head, new); 
    head->current = new;
}

static inline void list_replace(struct list_node *old, \
        struct list_node *new) {
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

static inline struct list_node *list_remove_head(
        struct list_head *head) {
    struct list_node *current = head->current;
    
    head->current = current->next;
    if(!_list_remove(current)) {
        head->current = NULL;
    }

    return current;
}

static inline struct list_node *list_remove_tail(
        struct list_head *head) {
    struct list_node *tail = head->current->prev;

    if(!_list_remove(tail)) {
        head->current = NULL;
    }

    return tail;
}

#endif // _LIST_H
