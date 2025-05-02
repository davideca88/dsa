#include "../include/binary_tree.h"


BinTree new_bintree() {
    return NULL;
}

   
BinTree binsert(BinTree t, int data) {
    if(t == NULL) {
        BinTree new = (BinTree) malloc(sizeof(Node));
        
        new->l = NULL;
        new->r = NULL;
        new->data = data;

        return new;   
    }
    
    if(data < t->data) {
        t->l = binsert(t->l, data);
    }
    
    else if(data > t->data) {
        t->r = binsert(t->r, data);
    }
    
    return t;
}


void bwalk(BinTree t, void(*visit)(BinTree t), char walk_mode) {
    if(t == NULL)
        return;
    
    switch (walk_mode){
        case INORDER:
            bwalk(t->l, visit, walk_mode);
            (*visit)(t);
            bwalk(t->r, visit, walk_mode);
            break;
        case PREORDER:
            (*visit)(t);
            bwalk(t->l, visit, walk_mode);
            bwalk(t->r, visit, walk_mode);
            break;
        case POSTORDER:
            bwalk(t->l, visit, walk_mode);
            bwalk(t->r, visit, walk_mode);
            (*visit)(t);
            break;
    }
}


void print_node(BinTree t) {
    printf("%d ", t->data);
}


void print_tree(BinTree t, char print_mode) {
    bwalk(t, print_node, print_mode);
}
