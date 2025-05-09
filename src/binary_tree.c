#include "../include/binary_tree.h"
#define MAX_DATA  ((1 << 14) - 1)

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

BinTree binsert_by_id(BinTree t, uint32_t package) {
    if(t == NULL) {
        BinTree new = (BinTree) malloc(sizeof(Node));
        
        new->l = NULL;
        new->r = NULL;
        new->data = package;

        return new;   
    }
    int id_root = t->data >> 14;
    int id_new  = package >> 14;

    if (id_new < id_root) {
        t->l = binsert_by_id(t->l, package);
    } else if(id_new > id_root) {
        t->r = binsert_by_id(t->r, package);
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

void print_node2(BinTree t) {
    printf("ID: %d DATA: %d\n", t->data>>14,t->data & MAX_DATA);
}

void print_tree(BinTree t,char option, char print_mode) {
    switch (option)
    {
    case 0:
        bwalk(t, print_node, print_mode);
        break;
    
    case 1:
        bwalk(t,print_node2,print_mode);
        break;
    }
}

void node_to_file(BinTree t, size_t n, va_list ap) {
    fwrite(&(t->data), sizeof(uint32_t), 1, va_arg(ap, FILE*));
}

void tree_to_file(BinTree t, FILE *fd) {
    vbwalk(t, node_to_file, INORDER, 1, fd);
}

void rpfile(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("error opening file");
        return;
    }

    uint32_t val;
    while (fread(&val, sizeof(int), 1, f) == 1) {
        printf("ID: %d DATA: %d\n", val>>14, val & MAX_DATA);
    }

    printf("\n");
    fclose(f);
}

BinTree arvbin_vec(BinTree root, Vector v, int t, int mode){
    switch (mode)
    {
    case 0:
        for(int i = 0; i < t; i++){
            root = binsert(root,v[i]);
        }
        break;
    
    case 1:
        for (int i = 0; i < t; i++){
            root = binsert_by_id(root,v[i]);
        }
        break;
    }
    return root;
}

int arvbin_Search(BinTree raiz, int d){
    if(raiz == NULL){
        return -1;
    }
    else{
        if(raiz->data == d){
            return raiz->data;
        }else{

            if(raiz->data < d){
                return arvbin_Search(raiz->r,d);
            }
            else{
                return arvbin_Search(raiz->l,d);
            }
        }
    }
}

int count_nodes(BinTree root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->l) + count_nodes(root->r);
}


int height_binTree(BinTree root) {
    if (root == NULL) {
        return -1; // Árvore vazia tem altura -1 (ou 0, se considerar folha como altura 1)
    } else {
        // Calcula a altura das subárvores esquerda e direita
        int heightL = height_binTree(root->l);
        int heightR = height_binTree(root->r);
        
        // Retorna a maior altura + 1 (contando o nó atual)
        return (heightL > heightR) ? heightL + 1 : heightR + 1;
    }
}


void delete_BST(BinTree t){

    if(t == NULL) return;

    delete_BST(t->l);
    delete_BST(t->r);

    free(t);


}