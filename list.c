#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
     return list;
}

void * firstList(List * list) {
  list->current = list->head;
    return (void *)list->current->data;
}

void * nextList(List * list) {
  if(list->current && list->current->next != NULL){
    list->current = list->current->next;
    return (void *)list->current->data;
  }else{
    return NULL;
  }
}

void * lastList(List * list) {
  list->current = list->tail;
    return (void *)list->current->data;
}

void * prevList(List * list) {
  if(list->current && list->current->prev != NULL){
    list->current = list->current->prev;
    return (void *)list->current->data;
  }else{
    return NULL;
  }
}

void pushFront(List * list, const void * data) {
  Node *x = createNode(data);
  if(list->head){
    x->next = list->head;
    list->head->prev = x;
  }else{
    list->tail = x;
  }
  list->head = x;
  x->prev = NULL;
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node *x = createNode(data);
  if(list->current->next == NULL){
    x->prev = list->current;
    list->tail = x;
    list->current->next = list->tail;
    x->next = NULL;
  }else{
    x->prev = list->current;
    list->current->next = x;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list->current->next && list->current->prev == NULL){
    list->current = NULL;
  }
  if((list->current->prev == NULL) && (list->current->next != NULL)){
    list->head = list->current->next;
    list->head->prev = NULL;
    list->current = NULL;
  }
  if((list->current->prev != NULL) && (list->current->next == NULL)){
    list->tail = list->current->prev;
    list->tail->next = NULL;
    list->current = NULL;
  }
  return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}