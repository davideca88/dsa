#include "../include/list.h"


// Cria uma lista 
List new_list() {
    struct _list_s *l = (struct _list_s*) malloc(sizeof(struct _list_s));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

// Retorna o tamanho da lista
size_t llen(List l) {
    return l->len;
}

// Insere na cabeça (head) da lista
int linserth(List l, int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = l->head;
    l->head = node;
    
    if(l->tail == NULL) {
        l->tail = node;
    }
    
    l->len++;
    return data;
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

// Remove um nó de índice. Retorna o dado do nó removido. Retorna INT_MAX se não encontrar o elemento
int lremove(List l, size_t i) {
    Node *node = l->head;
    Node *prev;
    size_t pos = 0;
    int data;
    
    if(l->len) {

        if(i == 0) {
            node = l->head;
            l->head = node->next;
        }
        else if(i < l->len) {
            while(pos < i) {
                prev = node;
                node = node->next;
                pos++;
            }
            prev->next = node->next;
            data = node->data;
        }
        
            free(node);
            l->len--;
            return data;
            
    }
    return INT_MAX;
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

// Transforma um vetor em uma lista
size_t array_to_list(List l, int arr[], size_t arr_len) {
    Node *node = l->head;
   
    if(l->len == 0) {
        for(size_t i = 0; i < arr_len; i++) {
            linsertt(l, arr[i]);
        }
        return l->len;
    }

    return INT_MAX;
}
