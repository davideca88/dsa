#include "../include/avltree.h"

// Nó sentinela para reduzir as comparações
AvlNode _NullNode = {
    NULL,
    NULL,
    0,
    -1 // facilita cálculo da altura
};

Avl NullNode = &_NullNode;

Avl new_avl() {
    return NullNode;
}

i8 avl_height(Avl t) {
    return t == NullNode ? 0 : t->height;
}

void avl_update_height(Avl t) {
    i8 hl = t->l->height;
    i8 hr = t->r->height;

    t->height = 1 + MAX(hl, hr);
}

i8 avl_balance_factor(Avl t) {
    return (avl_height(t->l) - avl_height(t->r));
}

Avl avl_r_rotate(Avl t) {
    Avl aux;
    
    aux = t->l;        
    t->l = aux->r;
    aux->r = t;

    avl_update_height(t);
    avl_update_height(aux);
    
    return aux;
}

Avl avl_l_rotate(Avl t) {
    Avl aux;

    aux = t->r;
    t->r = aux->l;
    aux->l = t;
    
    avl_update_height(t);
    avl_update_height(aux);
        
    return aux;
}

Avl avl_balance(Avl t) {
    avl_update_height(t);

    i8 bf = avl_balance_factor(t);

    if(bf > 1) {
        if(avl_balance_factor(t->l) < 0) {
            t->l = avl_l_rotate(t->l);
        }
        return avl_r_rotate(t);
    }

    if(bf < -1) {
        if(avl_balance_factor(t->r) > 0) {
            t->r = avl_r_rotate(t->r);
        }
        return avl_l_rotate(t);
    }

    return t;
}

Avl avl_insert(Avl t, u32 data) {
    if(t == NullNode) {
        Avl new = (Avl) malloc(sizeof(AvlNode));
        new->l = NullNode;
        new->r = NullNode;
        new->data = data;
        new->height = 0;
         
        return new;
    }

    if(data < t->data) {
        t->l = avl_insert(t->l, data);
    }
    
    else if(data > t->data) {
        t->r = avl_insert(t->r, data);
    }
    
    else {
        return t;
    }

    return avl_balance(t);
}

Avl avl_search(Avl t, u32 data) {
    if(t == NullNode)
        return NULL;

    if(data < t->data) {
        return avl_search(t->l, data);
    }
    else if(data > t->data) {
        return avl_search(t->r, data);
    }

    else {
        return t;
    }
}


void avl_walk(Avl t, void(*visit)(Avl t), char walk_mode) {
    if(t == NullNode)
        return;
    
    switch (walk_mode){
        case INORDER:
            avl_walk(t->l, visit, walk_mode);
            (*visit)(t);
            avl_walk(t->r, visit, walk_mode);
            break;
        case PREORDER:
            (*visit)(t);
            avl_walk(t->l, visit, walk_mode);
            avl_walk(t->r, visit, walk_mode);
            break;
        case POSTORDER:
            avl_walk(t->l, visit, walk_mode);
            avl_walk(t->r, visit, walk_mode);
            (*visit)(t);
            break;
    }
}

void avl_print_node(Avl t) {
    printf("%d ", t->data);
}

void avl_print(Avl t, char print_mode) {
    avl_walk(t, avl_print_node, print_mode);
}

void delete_avl(Avl t) {
    if(t == NULL) return;

    delete_avl(t->l);
    delete_avl(t->r);
}
