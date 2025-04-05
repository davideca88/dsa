#include "../include/list.h"


// Cria uma lista 
List new_list() {
    struct _list_s *l = (struct _list_s*) malloc(sizeof(struct _list_s));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

// Retorna o dado contido no index i da lista
int lindex(List l, size_t i) {
    Node *node = l->head;
    size_t pos = 0;

    while(pos < i) {
        node = node->next;
        pos++;
    }
    
    return node->data;
}

// Insere na cauda (tail) da lista
int linsertt(List l, int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    
    if(l->tail) {
        l->tail->next = node;
    } else {
        l->head = node;
    }
    l->tail = node;
    
    l->len++;
    return data;
} 

// Imprime a lista no stdout e retorna o tamanho da lista
size_t print_list(List l) {
    Node *node;
    putchar('[');
    
    if(l->len) {
        node = l->head;
        printf("%d", node->data);
        node = node->next;
        
        while(node) {
            printf(", %d", node->data);
            node = node->next;
        }
    }
    
    putchar(']');
    
    return l->len;
}

// Transforma um vetor em uma lista. Retorna o tamanho da lista se conseguiu criar. Se não, retorna INT_MAX
size_t array_to_list(List l, Vector arr, size_t arr_len) {
    Node *node = l->head;
   
    if(l->len == 0) {
        for(size_t i = 0; i < arr_len; i++) {
            linsertt(l, arr[i]);
        }
        return l->len;
    }

    return INT_MAX;
}

// Busca sequencial na lista. Retorna bool se encontrou ou não
char lb_search(List l, int key) {
    Node *node = l->head;
    Node *prev;
    while(node && node->data != key) {
        prev = node;
        node = node->next;
    }
    if(node) {
        return 1;
    }
    return 0;
}
