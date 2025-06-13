#include "../include/avl_tree.h"

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

int8_t avl_height(Avl t) {
    return t == NullNode ? 0 : t->height;
}

void avl_update_height(Avl t) {
    int8_t hl = t->l->height;
    int8_t hr = t->r->height;

    t->height = 1 + max(hl, hr);
}

int8_t avl_balance_factor(Avl t) {
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

Avl avl_insert(Avl t, Keys data) {
    if(t == NullNode) {
        Avl new = (Avl) malloc(sizeof(AvlNode));
        new->l = NullNode;
        new->r = NullNode;
        new->data = data;
        new->height = 0;
         
        return new;
    }

    if(data.id < t->data.id) {
        t->l = avl_insert(t->l, data);
    }
    
    else if(data.id > t->data.id) {
        t->r = avl_insert(t->r, data);
    }
    
    else {

        return t;
    }

    return avl_balance(t);
}


void avl_print_node(const char* nomeArquivo, Avl t) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
       
        return;
    }

    if (fseek(file,t->data.offset, SEEK_SET) != 0) {
        perror("Erro ao tentar posicionar no arquivo");
        return;
    }

    Product produtoLido;


    if (fread(&produtoLido, sizeof(Product), 1, file) != 1) {
        fprintf(stderr, "Erro: Não foi possível ler o produto no registro %lu\n", t->data.offset);
        return;
    }

    printf("ID %lu -> Produto: %s\n",produtoLido.id, produtoLido.name);

    fclose(file);

}

Avl avl_search(Avl t, Key id) {
    if(t == NullNode)
        return NULL;

    if(id < t->data.id) {
        return avl_search(t->l, id);
    }
    else if(id > t->data.id) {
        return avl_search(t->r, id);
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


void avl_print(const char* nomeArquivo, Avl t, char print_mode) {
    avl_walk2(t, nomeArquivo, print_mode);
}






void avl_walk2(Avl t,const char* nomeArquivo, char walk_mode) {
    if(t == NullNode)
        return;
    
    switch (walk_mode){
        case INORDER:
            avl_walk2(t->l, nomeArquivo, walk_mode);
            avl_print_node(nomeArquivo,t);
            avl_walk2(t->r, nomeArquivo, walk_mode);
            break;
        case PREORDER:
            avl_print_node(nomeArquivo,t);
            avl_walk2(t->l, nomeArquivo, walk_mode);
            avl_walk2(t->r, nomeArquivo, walk_mode);
            break;
        case POSTORDER:
            avl_walk2(t->l, nomeArquivo, walk_mode);
            avl_walk2(t->r, nomeArquivo, walk_mode);
            avl_print_node(nomeArquivo,t);
            break;
    }
}

// Avl avl_vec(Avl root, Vector v, size_t t){
//     for(size_t i = 0; i < t; i++){
//         root = avl_insert(root,v[i]);
//     }
    
//     return root;

//}

void delete_avl_node(Avl t) {
    free(t);
}

void delete_AVL(Avl t){
    avl_walk(t, delete_avl_node, POSTORDER);
}



//Funções para a AVL de Prices



Range new_range() {
    Range new = (Range) malloc(sizeof(struct _range_node_s));
    new->head = NULL;
    new->tail = NULL;
    new->len = 0;

    return new;
}

void rinsert(Range r, Prices prices) {
    RangeNode *new = (RangeNode*) malloc(sizeof(RangeNode));
    new->data = prices;
    new->next = NULL;
    
    if(r->tail) {
        r->tail->next = new;
    } else {
        r->head = new;
    }
    r->tail = new;
    
    r->len++;
}

Prices range_index(Range r, size_t index) {
RangeNode *node = r->head;
    size_t pos = 0;

    while(pos < index) {
        node = node->next;
        pos++;
    }
    
    return node->data;
}

void clear_range(Range r) {
    RangeNode *node = r->head;
    RangeNode *next;

    while(node) {
        next = node->next;
        free(node);
        node = next;
    }
    r->head = NULL;
    r->tail = NULL;
    r->len = 0;
}

// Nó sentinela para reduzir as comparações (AVL_Prices)
AvlNodePrices _NullNodeP = {
    NULL,
    NULL,
    NULL,
    0,
    -1 // facilita cálculo da altura
};

AvlPrices NullNodeP = &_NullNodeP;

AvlPrices new_avl_Prices() {
    return NullNodeP;
}

int8_t avl_prices_height(AvlPrices t) {
    return t == NullNodeP ? 0 : t->height;
}

void avl_prices_update_height(AvlPrices t) {
    int8_t hl = t->l->height;
    int8_t hr = t->r->height;

    t->height = 1 + max(hl, hr);
}

int8_t avl_prices_balance_factor(AvlPrices t) {
    return (avl_prices_height(t->l) - avl_prices_height(t->r));
}

AvlPrices avl_prices_r_rotate(AvlPrices t) {
    AvlPrices aux;
    
    aux = t->l;        
    t->l = aux->r;
    aux->r = t;

    avl_prices_update_height(t);
    avl_prices_update_height(aux);
    
    return aux;
}

AvlPrices avl_prices_l_rotate(AvlPrices t) {
    AvlPrices aux;

    aux = t->r;
    t->r = aux->l;
    aux->l = t;
    
    avl_prices_update_height(t);
    avl_prices_update_height(aux);

    return aux;
}

AvlPrices avl_prices_balance(AvlPrices t) {
    avl_prices_update_height(t);

    int8_t bf = avl_prices_balance_factor(t);

    if(bf > 1) {
        if(avl_prices_balance_factor(t->l) < 0) {
            t->l = avl_prices_l_rotate(t->l);
        }
        return avl_prices_r_rotate(t);
    }

    if(bf < -1) {
        if(avl_prices_balance_factor(t->r) > 0) {
            t->r = avl_prices_r_rotate(t->r);
        }
        return avl_prices_l_rotate(t);
    }

    return t;
}


AvlPrices avl_prices_insert(AvlPrices t, Prices data) {
    if(t == NullNodeP) {
        AvlPrices new = (AvlPrices) malloc(sizeof(AvlNodePrices));
        new->l = NullNodeP;
        new->r = NullNodeP;
        new->d = NullNodeP;
        new->data = data;
        new->height = 0;
         
        return new;
    }

    if(data.price < t->data.price) {
        t->l = avl_prices_insert(t->l, data);
    }
    
    else if(data.price > t->data.price) {
        t->r = avl_prices_insert(t->r, data);
    }
    
    else {

        t->d = avl_prices_insert(t->d, data);
        return t;
    }

    return avl_prices_balance(t);
}


void avl_prices_print_node(const char* nomeArquivo, AvlPrices t) {
    AvlPrices aux = t;
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    while(aux != NullNodeP) {
    
        if (aux->data.offset >= file_size) {
            fprintf(stderr, "Aviso: Índice %lu inválido (arquivo tem apenas %ld bytes)\n", 
                   aux->data.offset, file_size);
            aux = aux->d;
            continue;
        }

        if (fseek(file, aux->data.offset, SEEK_SET) != 0) {
            perror("Erro ao posicionar no arquivo");
            break;
        }

        Product produtoLido;
        if (fread(&produtoLido, sizeof(Product), 1, file) != 1) {
            fprintf(stderr, "Erro ao ler produto no índice %lu\n", aux->data.offset);
            break;
        }

        printf("ID %lu -> Produto: %s -> Preço: %u\n", 
               produtoLido.id, produtoLido.name, produtoLido.price);
        aux = aux->d;
    }

    fclose(file);
}



void avl_prices_print(const char* nomeArquivo, AvlPrices t, char print_mode) {
    avl_prices_walk(t, nomeArquivo, print_mode);
}






void avl_prices_walk(AvlPrices t,const char* nomeArquivo, char walk_mode) {
    if(t == NullNodeP)
        return;
    
    switch (walk_mode){
        case INORDER:
            avl_prices_walk(t->l, nomeArquivo, walk_mode);
            avl_prices_print_node(nomeArquivo,t);
            avl_prices_walk(t->r, nomeArquivo, walk_mode);
            break;
        case PREORDER:
            avl_prices_print_node(nomeArquivo,t);
            avl_prices_walk(t->l, nomeArquivo, walk_mode);
            avl_prices_walk(t->r, nomeArquivo, walk_mode);
            break;
        case POSTORDER:
            avl_prices_walk(t->l, nomeArquivo, walk_mode);
            avl_prices_walk(t->r, nomeArquivo, walk_mode);
            avl_prices_print_node(nomeArquivo,t);
            break;
    }
}

AvlPrices avl_prices_search(AvlPrices t, Price price) {
    if(t == NullNodeP)
        return NULL;

    if(price < t->data.price) {
        return avl_prices_search(t->l, price);
    }
    else if(price > t->data.price) {
        return avl_prices_search(t->r, price);
    }

    else {
        return t;
    }
}





void avl_prices_walk2(AvlPrices t, void(*visit)(AvlPrices t), char walk_mode) {
    if(t == NullNodeP)
        return;
    
    switch (walk_mode){
        case INORDER:
            avl_prices_walk2(t->l, visit, walk_mode);
            (*visit)(t);
            avl_prices_walk2(t->r, visit, walk_mode);
            break;
        case PREORDER:
            (*visit)(t);
            avl_prices_walk2(t->l, visit, walk_mode);
            avl_prices_walk2(t->r, visit, walk_mode);
            break;
        case POSTORDER:
            avl_prices_walk2(t->l, visit, walk_mode);
            avl_prices_walk2(t->r, visit, walk_mode);
            (*visit)(t);
            break;
    }
}







void delete_avl_prices_node(AvlPrices t) {
    free(t);
}

void delete_AVL_prices(AvlPrices t){
    avl_prices_walk2(t, delete_avl_prices_node, POSTORDER);
}







//Funções que passam de um arquivo para AVL

Avl criarAVLDeIndicesKey(const char* nomeArquivo, Avl t) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
       
        return NULL;
    }

   
    Product produtoTemp;
    Keys keysAVL;
    unsigned i = 0;
    while(fread(&produtoTemp, sizeof(Product), 1, file) == 1){

        keysAVL.offset = i*(sizeof(Product));
        keysAVL.id = produtoTemp.id;

        t = avl_insert(t,keysAVL);

        i++;
       
    }
    

    fclose(file);

    return t;
}



AvlPrices criarAVLDeIndicesPrices(const char* nomeArquivo, AvlPrices t) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return NULL;
    }

    Product produtoTemp;
    Prices PriceAVL;
    unsigned i = 0;
    
   
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    unsigned max_records = file_size / sizeof(Product);

    while(fread(&produtoTemp, sizeof(Product), 1, file) == 1 && i < max_records) {
        PriceAVL.offset = i * sizeof(Product);
        PriceAVL.price = produtoTemp.price;

        t = avl_prices_insert(t, PriceAVL);
        i++;
    }

    fclose(file);
    return t;
}


//Funções para maior menor


void printInOrderWithConditions(AvlPrices t, Range r, unsigned min, unsigned max, bool includeMin, bool includeMax) {
    if (t == NullNodeP) return;
   
    if (t->data.price > min || (includeMin && t->data.price == min)) {
        printInOrderWithConditions(t->l, r, min, max, includeMin, includeMax);
    }
    
  
    bool satisfiesMin = includeMin ? (t->data.price >= min) : (t->data.price > min);
    bool satisfiesMax = includeMax ? (t->data.price <= max) : (t->data.price < max);
    
    if (satisfiesMin && satisfiesMax) {
//        avl_prices_print_node(nomeArquivo, t); 
    }
    
    
    if (t->data.price < max || (includeMax && t->data.price == max)) {
        printInOrderWithConditions(t->r, r, min, max, includeMin, includeMax);
    }
}

void avl_prices_make_range(AvlPrices t, Range r, unsigned min, unsigned max, bool includeMin, bool includeMax) {
    if (t == NullNodeP) return;
   
    if (t->data.price > min || (includeMin && t->data.price == min)) {
        printInOrderWithConditions(t->l, r, min, max, includeMin, includeMax);
    }
    
  
    bool satisfiesMin = includeMin ? (t->data.price >= min) : (t->data.price > min);
    bool satisfiesMax = includeMax ? (t->data.price <= max) : (t->data.price < max);
    
    if (satisfiesMin && satisfiesMax) {
        rappend(r, t->data);
    }
    
    
    if (t->data.price < max || (includeMax && t->data.price == max)) {
        printInOrderWithConditions(t->r, r, min, max, includeMin, includeMax);
    }
}

void printRange(const char* nomeArquivo, AvlPrices t, unsigned min, unsigned max, bool includeMin, bool includeMax) {
    printf("Valores na arvore que sao ");
    printf(includeMin ? "maiores ou iguais a %u" : "maiores que %u", min);
    printf(" e ");
    printf(includeMax ? "menores ou iguais a %u:\n" : "menores que %u:\n", max);
    
    printInOrderWithConditions(nomeArquivo, t, min, max, includeMin, includeMax);
    printf("\n\n");
}
