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

// 1. createList: allocate and initialize a new List with all pointers set to NULL
List * createList() {
    List * list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

// 2. firstList: return data of head node and set current to head
//    nextList: return data of node after current and advance current
void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

// 3. lastList: return data of tail node and set current to tail
//    prevList: return data of node before current and move current back
void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

// 4. pushFront: insert a new node at the beginning of the list
void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

// 5. pushCurrent: insert a new node after the current node
void pushCurrent(List * list, void * data) {
    Node * new = createNode(data);
    if (list->current == NULL) {
        // List is empty
        list->head = new;
        list->tail = new;
    } else {
        new->prev = list->current;
        new->next = list->current->next;
        if (list->current->next != NULL) {
            list->current->next->prev = new;
        } else {
            list->tail = new;
        }
        list->current->next = new;
    }
    list->current = new;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. popCurrent: remove the current node and return its data
//    current is updated to point to the next node after removal
void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    Node * toRemove = list->current;
    void * data = toRemove->data;

    if (toRemove->prev != NULL) {
        toRemove->prev->next = toRemove->next;
    } else {
        list->head = toRemove->next;
    }

    if (toRemove->next != NULL) {
        toRemove->next->prev = toRemove->prev;
    } else {
        list->tail = toRemove->prev;
    }

    list->current = toRemove->next;

    free(toRemove);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
