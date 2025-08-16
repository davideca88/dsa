#include "../include/llist.h"

// Cria uma lista 
LinkedList new_list() {
    struct llist *l = (struct llist*) malloc(sizeof(struct llist));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

// Deleta uma lista
LinkedList delete_list(LinkedList l) {
    struct llist_node *node2 = l->head;
    struct llist_node *next;

    while(node2) {
        next = node2->next;
        free(node2);
        node2 = next;
    }
    
    return NULL;
}

// Retorna o dado contido no index i da lista
int lindex(LinkedList l, size_t i) {
    struct llist_node *node2 = l->head;
    size_t pos = 0;

    while(pos < i) {
        node2 = node2->next;
        pos++;
    }
    
    return node2->data;
}

// Insere na cauda (tail) da lista
int linsertt(LinkedList l, int data) {
    struct llist_node *node2 = (struct llist_node*) malloc(sizeof(struct llist_node));
    node2->data = data;
    node2->next = NULL;
    
    if(l->tail) {
        l->tail->next = node2;
    } else {
        l->head = node2;
    }
    l->tail = node2;
    
    l->len++;
    return data;
} 

// Imprime a lista no stdout e retorna o tamanho da lista
size_t print_llist(LinkedList l) {
    struct llist_node *node2;
    putchar('[');
    
    if(l->len) {
        node2 = l->head;
        printf("%d", node2->data);
        node2 = node2->next;
        
        while(node2) {
            printf(", %d", node2->data);
            node2 = node2->next;
        }
    }
    
    putchar(']');
    
    return l->len;
}

// Busca sequencial na lista. Retorna bool se encontrou ou não
char ls_search(LinkedList l, int key) {
    struct llist_node *node2 = l->head;
    while(node2 && node2->data != key) {
        node2 = node2->next;
    }
    if(node2) {
        return 1;
    }
    return 0;
}
