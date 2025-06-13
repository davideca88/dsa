#include "../include/index.h"

bool load(Index idx) {
    Product product;
    Offset offset = 0;
    rewind(idx->rec_fd);
    
    switch(idx->mode) {
        case HASH_TABLE:
            HashTable ht = (HashTable) idx->idx_p;

            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                ht->insert(ht, product.id, offset);
                offset = ftell(idx->rec_fd);
            }
            return true;
        case AVL_EQ:
            Avl *t = (Avl*) &(idx->idx_p);
            while(fread(&product, sizeof(Product), 1, idx->rec_fd)) {
                *t = avl_insert(*t, ((Keys){offset, product.id}));
                offset = ftell(idx->rec_fd);
            }
            return true;
    }
    return false;
}

bool hash_table_insert(Index idx, Product product) {
    fseek(idx->rec_fd, 0, SEEK_END);
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

Product avl_eq_search(Index idx, Key key) {
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

bool avl_eq_insert(Index idx, Product product) {
    fseek(idx->rec_fd, 0, SEEK_END);
    idx->idx_p = avl_insert((Avl) idx->idx_p, ((Keys){ftell(idx->rec_fd), product.id}));
    return true;
}

bool avl_range_insert(Index idx, Product product);

Product avl_range_search(Index idx, Price price);

bool avl_rquery(Index idx, char fint, Price fprice, char lint, Price lprice) {
    if(idx->mode != AVL_RANGE) {
        puts("Only price indexing has range query");
        return false;
    }
    clear_range(idx->last_rquery);
    avl_prices_make_range(idx->idx_p, idx->last_rquery, fprice, lprice, fint, lint);
    return true;
}

Index create_index(const char* rec_name, size_t len, const char* key_mode, ...) {
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
    idx->load = load;
    
    if(!strcmp(key_mode, "price")) {
        idx->idx_p = new_avl_Prices();
        idx->mode = AVL_RANGE;
        
    }

    if(!strcmp(key_mode, "id")) {
        va_list ap;
        va_start(ap, key_mode);
        int arg = va_arg(ap, int);
        
        switch(arg) {
            case HASH_TABLE:
                idx->idx_p = new_hash_table(len, CHAINING);
                idx->mode = HASH_TABLE;
                idx->search = hash_table_search;
                idx->insert = hash_table_insert;
                
            break; // HASH_TABLE
            case AVL_EQ:
                idx->idx_p = new_avl();
                idx->mode = AVL_EQ;
                idx->search = avl_eq_search;
                idx->insert = avl_eq_insert;
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
