#include "../include/list.h"


// Cria uma lista 
List new_list() {
    struct _list_s *l = (struct _list_s*) malloc(sizeof(struct _list_s));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

// Deleta uma lista
List delete_list(List l) {
    Node *node = l->head;
    Node *next;

    while(node) {
        next = node->next;
        free(node);
        node = next;
    }
    
    return NULL;
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
// TODO: (!) Carece de testes
size_t vector_to_list(List l, Vector v, size_t v_len) {
    Node *node = l->head;
    Node *aux;
    size_t v_pos = 0;
    
    // Se a lista não for vazia, reaproveita-se os nós já existentes e muda o campo `data` e avança a posição no vetor
    if(l->len > 0) {
        while(node && v_pos < v_len) {
            aux = node;
            node->data = v[v_pos];
            v_pos++;
            node = node->next;
        }
        
        // Define-se a nova cauda para o caso do vetor ser menor do que a lista
        // Se for maior ou igual, só sobrescreverá com o mesmo valor
        l->tail = aux;
        
        // Se a o vetor for menor do que a lista, apaga os nós que ainda restam
        while(node) {
            aux = node;
            node = node->next;
            free(aux);
            l->len--;
        }
    }
    
    // Adiciona nós ao fim da lista. Se os nós foram reaproveitadas, só adiciona os que ainda faltam
    while(v_pos < v_len) {
        linsertt(l, v[v_pos]);
        v_pos++;
    }
    

    return l->len == v_len ? v_len : INT_MAX;
}

// Busca sequencial na lista. Retorna bool se encontrou ou não
char ls_search(List l, int key) {
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
