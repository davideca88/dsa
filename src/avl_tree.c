#include "../include/avl_tree.h"

AvlNode _NullNode = {
    NULL,
    NULL,
    0,
    (int8_t) -1
};

Avl NullNode = &_NullNode;

Avl new_avl() {
    return NullNode;
}

uint8_t avl_height(Avl t) {
    return t == NullNode ? 0 : t->height;
}

void avl_update_height(Avl t) {
    uint8_t hl = t->l->height;
    uint8_t hr = t->r->height;

    t->height = 1 + max(hl, hr);
}

int8_t avl_balance_factor(Avl t) {
    return (int8_t) (t->l->height - t->r->height);
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

    int8_t bf = avl_balance_factor(t);

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

Avl avl_insert(Avl t, uint32_t data) {

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

Avl avl_search(Avl t, uint32_t data) {
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
