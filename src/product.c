#include "../include/product.h"

int compare(Price value, Operator op, Price reference) {
    switch (op) {
        case OP_GT:  return value > reference;
        case OP_GTE: return value >= reference;
        case OP_LT:  return value < reference;
        case OP_LTE: return value <= reference;
        case OP_EQ:  return value == reference;
        case OP_NEQ: return value != reference;
        default:     return 0;
    }
}

Product file_ssearch(FILE *fd, Key id) {
    if (!fd) {
        printf("Invalid file!\n");
        Product error = {0};
        return error;
    }

    rewind(fd);

    Product p;
    while (fread(&p, sizeof(Product), 1, fd) == 1) {
        if (p.id == id) {
            return p;
            printf("Não é esse\n");
        }
    }

    printf("Product ID %lu not found\n", id);
    Product error = {0};
    return error;
}


Range file_ssearch_range(FILE *fd, int use_low, int use_high, 
    Operator op_low, Price low, Operator op_high, Price high){
    if (!fd)
    {
        printf("Error opening file\n");
        Range error = {0};
        return error;
    }

    Range result = new_range();
    Product p;
    int found = 0;

    while (fread(&p, sizeof(Product), 1, fd) == 1)
    {
        int match = 1;
        if (use_low) {
            match = match && compare(p.price, op_low, low);
        }
        if (use_high) {
            match = match && compare(p.price, op_high, high);
        }

        if (match) {
            rappend(result, p);
            found++;
        }
    }

    if (!found)
    {
        printf("No products found in range\n");
        Range error = {0};
        fclose(fd);
        return error;
    }
    return result;
}

void print_product(Product product) {
    if(product.name[0] == '\0') return;
    
    unsigned short description_len = strlen(product.description);
    
    for(unsigned char i = 0; i < ROWS; i++) putchar('-');
    putchar('\n');

    printf("Name: %s\n", product.name);
    printf("Price: U$%d.%d%d\n", product.price / 100, product.price % 100 / 10, product.price % 10);
    printf("Quantity: %d pcs\n", product.quantity);

    printf("Description: ");
    unsigned char gap = strlen("Description: ");
    for(unsigned short i = gap, j = 0, k = 0; i < description_len + gap; i++, k++) {
        if(product.description[i - gap] == ' ') {
            for(j = 1; product.description[i - gap + j] != '\0' && product.description[i - gap + j] != ' '; j++);
            if((j + gap + (k % ROWS)) > ROWS) {
                product.description[i - gap] = '\n';
                k = 0;
            }
        }
        putchar(product.description[i - gap]);
    }
    putchar('\n');
     

    for(unsigned char i = 0; i < ROWS; i++) putchar('-');
    putchar('\n');
}

void print_range(Range range) {
    RangeNode *aux = range->head;
    while(aux) {
        print_product(aux->data);
        aux = aux->next;
    }
}

Range new_range() {
    Range new = (Range) malloc(sizeof(struct _range_node_s));
    new->head = NULL;
    new->tail = NULL;
    new->len = 0;

    return new;
}

void rappend(Range r, Product product) {
    RangeNode *new = (RangeNode*) malloc(sizeof(RangeNode));
    new->data = product;
    new->next = NULL;
    
    if(r->tail) {
        r->tail->next = new;
    } else {
        r->head = new;
    }
    r->tail = new;
    
    r->len++;
}

Product range_index(Range r, size_t index) {
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

