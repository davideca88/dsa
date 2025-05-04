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

// TODO
// não sei se varargs estão funcionando (ainda)

void _vbwalk(BinTree t, void(*visit)(BinTree t, size_t n, va_list args), char walk_mode, size_t n, va_list args) {    
    if(t == NULL)
        return;
    
    va_list args_cpy;
    va_copy(args_cpy, args); // Necessário copiar toda vez que for utilizar (cada chamada)
    
    switch (walk_mode){
        case INORDER:
            _vbwalk(t->l, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            (*visit)(t, n, args_cpy);

            va_copy(args_cpy, args);
            _vbwalk(t->r, visit, walk_mode, n, args_cpy);
            break;
        case PREORDER:
            (*visit)(t, n, args_cpy);

            va_copy(args_cpy, args);
            _vbwalk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            _vbwalk(t->r, visit, walk_mode, n, args_cpy);
            break;
        case POSTORDER:
            _vbwalk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            _vbwalk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            (*visit)(t, n, args_cpy);
            break;
    }

    va_end(args_cpy);
}

void vbwalk(BinTree t, void(*visit)(BinTree t, size_t n, va_list args), char walk_mode, size_t n, ...) {
    va_list ap;
    va_start(ap, n);

    _vbwalk(t, visit, walk_mode, n, ap);

    va_end(ap);
}


void print_node(BinTree t) {
    printf("%d ", t->data);
}

void node_to_file(BinTree t, size_t n, va_list ap) {
    fwrite(&(t->data), sizeof(int), 1, va_arg(ap, FILE*));
}

void tree_to_file(BinTree t, FILE *fd) {
    vbwalk(t, node_to_file, INORDER, 1, fd);
}


void print_tree(BinTree t, char print_mode) {
    bwalk(t, print_node, print_mode);
}

BinTree arvbin_vec(BinTree root, Vector v, int t){
    for(int i = 0; i < t; i++){
        root = binsert(root,v[i]);
    }
    return root;
}
