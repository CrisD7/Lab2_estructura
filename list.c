#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    assert(lista != NULL);
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return NULL;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {
    Node* nodo = createNode(data);
    if (list->head == NULL){
        list->head = nodo;
        list->tail = nodo;
        return;
    }
    nodo->next = list->head;
    list->head = nodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {
    Node* nodo = createNode(data);
    if (list->current == NULL){
        if(list->head == NULL){
            list->head = nodo;
            list->tail = nodo;
        }
        else{
            nodo->next = list->head;
            list->head->prev = nodo;
            list->head = nodo;
        }
        return;
    }
    nodo->prev = list->current;
    nodo->next = list->current->next;
    if(nodo->next == NULL){
        list->tail = nodo;
    }
    else nodo->next->prev = nodo;
    list->current->next = nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {
    if (list -> current == NULL) return NULL;
    Node* actual = list -> current;
    Node * prevElim = actual -> prev;
    Node * nextElim = actual -> next;
    
    void* dato_elim = actual -> data;
    if (prevElim != NULL){
        prevElim -> next = nextElim;
    }
    else list -> head = nextElim;
    
    if (nextElim != NULL){
        nextElim -> prev = prevElim;
    }
    else list -> tail = prevElim;
    
    free(actual);
    return dato_elim;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}