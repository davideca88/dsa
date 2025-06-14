#include "../include/index.h"
#include <stdio.h>

bool load(Index idx) {
    Product product;
    Offset offset = 0;
    rewind(idx->rec_fd);
    
    switch(idx->mode) {
        case HASH_TABLE: {
            HashTable ht = (HashTable) idx->idx_p;

            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                ht->insert(ht, product.id, offset);
                offset = ftell(idx->rec_fd);
            }
            return true;
        }
        case AVL_ID: {
            Avl *t = (Avl*) &(idx->idx_p);
            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                *t = avl_insert(*t, ((Keys){offset, product.id}));
                offset = ftell(idx->rec_fd);
            }
            return true;
        }
        case AVL_PRICE: {
            AvlPrices *t = (AvlPrices*) &(idx->idx_p);
            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                *t = avl_prices_insert(*t, ((Prices){offset, product.price}));
                offset = ftell(idx->rec_fd);
            }
            return true;
        }
    }
    return false;
}

// Hash table #####################################################################################################################################################

bool hash_table_insert(Index idx, Product product) {
    fseek(idx->rec_fd, 0, SEEK_END);
    fwrite(&product, sizeof(Product), 1, idx->rec_fd);
    return ((HashTable) idx->idx_p)->insert(idx->idx_p, product.id, ftell(idx->rec_fd));
}

Product hash_table_search(Index idx, Key key) {
    Offset offset = ((HashTable)idx->idx_p)->get(idx->idx_p, key);
    Product product = {
        .description = {'\0'},
        .name = {'\0'},
        .id = 0,
        .price = 0,
        .quantity = 0
    };

    if(offset != EOF) {
        fseek(idx->rec_fd, offset, SEEK_SET);
        fread(&product, sizeof(Product), 1, idx->rec_fd);
    }
    
    return product;

}

// ################################################################################################################################################################

// AVL equality  ###################################################################################################################################################

Product avl_id_search(Index idx, Key key) {
    Offset offset = avl_search(idx->idx_p, key)->data.offset;
    Product product = {
        .description = {'\0'},
        .name = {'\0'},
        .id = 0,
        .price = 0,
        .quantity = 0
    };
    if(offset != EOF) {
        fseek(idx->rec_fd, offset, SEEK_SET);
        fread(&product, sizeof(Product), 1, idx->rec_fd);
    }
    return product;
}

bool avl_id_insert(Index idx, Product product) {
    fseek(idx->rec_fd, 0, SEEK_END);
    fwrite(&product, sizeof(Product), 1, idx->rec_fd);
    idx->idx_p = avl_insert((Avl) idx->idx_p, ((Keys){ftell(idx->rec_fd), product.id}));
    return true;
}

// ################################################################################################################################################################

// AVL range ######################################################################################################################################################

bool avl_range_insert(Index idx, Product product) {
    fseek(idx->rec_fd, 0, SEEK_END);
    fwrite(&product, sizeof(Product), 1, idx->rec_fd);
    idx->idx_p = avl_prices_insert((AvlPrices) idx->idx_p, ((Prices){ftell(idx->rec_fd), product.price}));
    return true; 
}

Range avl_rquery(Index idx, char fint, Price fprice, char lint, Price lprice) {
    if(idx->mode != AVL_PRICE) {
        puts("Only \"price\" indexing has range query");
        return NULL;
    }
    PriceRange prange = new_prange();
    Product product;
    PriceRangeNode *aux;
    clear_range(idx->last_rquery);
    
    avl_prices_make_range(idx->idx_p, prange, fprice * 100, lprice * 100, fint, lint);
    aux = prange->head;

    while(aux) {
        fseek(idx->rec_fd, aux->data.offset, SEEK_SET);
        if(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
            rappend(idx->last_rquery, product);
        }
        aux = aux->next;
    }

    delete_prange(prange);
    return idx->last_rquery;
}

Product avl_range_search(Index idx, Key price) {
    Product product = {
        .description = {'\0'},
        .name = {'\0'},
        .id = 0,
        .price = 0,
        .quantity = 0
    };
    idx->rquery(idx, 1, price, 1, price);

    if(idx->last_rquery->len > 0) {
        product = idx->last_rquery->head->data;
    }
    
    return product;
}

// ################################################################################################################################################################

Index create_index(const char* rec_name, const char* key_mode, ...) {
    FILE* rec_fd = fopen(rec_name, "rb+");
    
    if(!rec_fd) {
        // Cria arquivo se não existir
        rec_fd = fopen(rec_name, "wb+");
    }
    
    if(!rec_fd) {
        puts("Falha ao abrir arquivo de registros =(");
        return NULL;
    }
    
    Index idx = (Index) malloc(sizeof(struct _index_s));

    idx->rec_fd = rec_fd;
    idx->rquery = avl_rquery;
    idx->last_rquery = new_range();
    idx->load = load;
    
    if(!strcmp(key_mode, "price")) {
        idx->idx_p = new_avl_Prices();
        idx->mode = AVL_PRICE;
        idx->search = avl_range_search;
        idx->insert = avl_range_insert;

        return idx;
    }

    if(!strcmp(key_mode, "id")) {
        va_list ap;
        va_start(ap, key_mode);
        int arg = va_arg(ap, int);
        
        switch(arg) {
            case HASH_TABLE:
                size_t len = va_arg(ap, size_t);
                idx->idx_p = new_hash_table(len, CHAINING);
                idx->mode = HASH_TABLE;
                idx->search = hash_table_search;
                idx->insert = hash_table_insert;
                
            break; // HASH_TABLE
            case AVL_ID:
                idx->idx_p = new_avl();
                idx->mode = AVL_ID;
                idx->search = avl_id_search;
                idx->insert = avl_id_insert;
            break; // AVL
            
            default:
                puts("Tipo de índice por \"id\" não reconhecido =(");
                free(idx);
                exit(EXIT_FAILURE);
            break;
        }
        
        va_end(ap);
        
        return idx;
    }
    
    puts("Modo de indexação não reconhecido =(");
    free(idx);
    return NULL;
}
