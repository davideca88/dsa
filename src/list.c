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
    Node2 *node2 = l->head;
    Node2 *next;

    while(node2) {
        next = node2->next;
        free(node2);
        node2 = next;
    }
    
    return NULL;
}

// Retorna o dado contido no index i da lista
int lindex(List l, size_t i) {
    Node2 *node2 = l->head;
    size_t pos = 0;

    while(pos < i) {
        node2 = node2->next;
        pos++;
    }
    
    return node2->data;
}

// Insere na cauda (tail) da lista
int linsertt(List l, int data) {
    Node2 *node2 = (Node2*) malloc(sizeof(Node2));
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
size_t print_list(List l) {
    Node2 *node2;
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

// Transforma um vetor em uma lista. Retorna o tamanho da lista se conseguiu criar. Se não, retorna INT_MAX
// TODO: (!) Carece de testes
size_t vector_to_list(Vector v, List l, size_t v_len) {
    Node2 *node2 = l->head;
    Node2 *aux = node2;
    size_t v_pos = 0;
    
    // Se a lista não for vazia, reaproveita-se os nós já existentes e muda o campo `data` e avança a posição no vetor
    if(l->len > 0) {
        while(node2 && v_pos < v_len) {
            aux = node2;
            node2->data = v[v_pos];
            v_pos++;
            node2 = node2->next;
        }
        
        // Define-se a nova cauda para o caso do vetor ser menor do que a lista
        // Se for maior ou igual, só sobrescreverá com o mesmo valor
        if(node2) {
            l->tail = aux;
            aux->next = NULL;
        } else {
            l->tail = node2;
        }

        // Se a o vetor for menor do que a lista, apaga os nós que ainda restam
        while(node2) {
            aux = node2;
            node2 = node2->next;
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
    Node2 *node2 = l->head;
    while(node2 && node2->data != key) {
        node2 = node2->next;
    }
    if(node2) {
        return 1;
    }
    return 0;
}
