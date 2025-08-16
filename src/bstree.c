#include "../include/bstree.h"

Bst new_bst() {
    return NULL;
}

   
Bst bst_insert(Bst t, int data) {
    if(t == NULL) {
        Bst new = (Bst) malloc(sizeof(struct bst_node));
        
        new->l = NULL;
        new->r = NULL;
        new->data = data;

        return new;   
    }
    
    if(data < t->data) {
        t->l = bst_insert(t->l, data);
    }
    
    else if(data > t->data) {
        t->r = bst_insert(t->r, data);
    }
    
    return t;
}

void bst_walk(Bst t, void(*visit)(Bst t), char walk_mode) {
    if(t == NULL)
        return;
    
    switch (walk_mode){
        case INORDER:
            bst_walk(t->l, visit, walk_mode);
            (*visit)(t);
            bst_walk(t->r, visit, walk_mode);
            break;
        case PREORDER:
            (*visit)(t);
            bst_walk(t->l, visit, walk_mode);
            bst_walk(t->r, visit, walk_mode);
            break;
        case POSTORDER:
            bst_walk(t->l, visit, walk_mode);
            bst_walk(t->r, visit, walk_mode);
            (*visit)(t);
            break;
    }
}

// TODO
// não sei se varargs estão funcionando (ainda)

void _vbst_walk(Bst t, void(*visit)(Bst t, size_t n, va_list args), char walk_mode, size_t n, va_list args) {    
    if(t == NULL)
        return;
    
    va_list args_cpy;
    va_copy(args_cpy, args); // Necessário copiar toda vez que for utilizar (cada chamada)
    
    switch (walk_mode){
        case INORDER:
            _vbst_walk(t->l, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            (*visit)(t, n, args_cpy);

            va_copy(args_cpy, args);
            _vbst_walk(t->r, visit, walk_mode, n, args_cpy);
            break;
        case PREORDER:
            (*visit)(t, n, args_cpy);

            va_copy(args_cpy, args);
            _vbst_walk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            _vbst_walk(t->r, visit, walk_mode, n, args_cpy);
            break;
        case POSTORDER:
            _vbst_walk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            _vbst_walk(t->r, visit, walk_mode, n, args_cpy);

            va_copy(args_cpy, args);
            (*visit)(t, n, args_cpy);
            break;
    }

    va_end(args_cpy);
}

void vbst_walk(Bst t, void(*visit)(Bst t, size_t n, va_list args), char walk_mode, size_t n, ...) {
    va_list ap;
    va_start(ap, n);

    _vbst_walk(t, visit, walk_mode, n, ap);

    va_end(ap);
}

int bst_search(Bst raiz, int d){
    if(raiz == NULL){
        return -1;
    }
    else{
        if(raiz->data == d){
            return raiz->data;
        }else{

            if(raiz->data < d){
                return bst_search(raiz->r,d);
            }
            else{
                return bst_search(raiz->l,d);
            }
        }
    }
}

int bst_count_nodes(Bst root) {
    if (root == NULL) return 0;
    return 1 + bst_count_nodes(root->l) + bst_count_nodes(root->r);
}


int bst_height(Bst root) {
    if (root == NULL) {
        return -1; // Árvore vazia tem altura -1 (ou 0, se considerar folha como altura 1)
    } else {
        // Calcula a altura das subárvores esquerda e direita
        int heightL = bst_height(root->l);
        int heightR = bst_height(root->r);
        
        // Retorna a maior altura + 1 (contando o nó atual)
        return (heightL > heightR) ? heightL + 1 : heightR + 1;
    }
}


Bst delete_bst(Bst t){
    if(t == NULL) {
        return NULL;
    }
    delete_bst(t->l);
    delete_bst(t->r);
    free(t);
    return NULL;
}
