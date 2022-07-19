#include "pila.h"
#include <stdlib.h>
#include <assert.h>

struct _Pila {  
  struct GNode *top;
  int size;
};

struct GNode {
  void *data;
  struct GNode *next;
};

Pila pila_crear() {
  Pila newPila = malloc(sizeof(struct _Pila));
  newPila->top = NULL;
  newPila->size = 0; 
  return newPila;
}

void pila_destruir(Pila pila, FuncionDestructora destruir) {
  assert(pila != NULL);
  struct GNode* nodeToDelete;
  while (pila->top != NULL) {
    nodeToDelete = pila->top;
    pila->top = pila->top->next;
    destruir(nodeToDelete->data);
    free(nodeToDelete);
  }
  free(pila);
}

int pila_es_vacia(Pila pila) {
  assert(pila != NULL);
  return pila->top == NULL;
}

void* pila_tope(Pila pila) {
  assert(pila != NULL);
  assert(!pila_es_vacia(pila));
  return pila->top->data;
}

int pila_size(Pila pila) {
  assert(pila != NULL);
  return pila->size;
}

void pila_apilar(Pila pila, void *dato, FuncionCopia copiar) {
  assert(pila != NULL);
  struct GNode *newNode = malloc(sizeof(struct GNode));
  assert(newNode != NULL);
  newNode->next = pila->top;
  newNode->data = copiar(dato);
  pila->top = newNode;
  pila->size++;
}

void pila_desapilar(Pila pila, FuncionDestructora destroy) {
  assert(pila != NULL);
  if(!pila_es_vacia(pila)) {
    struct GNode* aEliminar = pila->top;
    pila->top = pila->top->next;
    destroy(aEliminar->data);
    free(aEliminar);
    pila->size--;
  }
}

void pila_imprimir(Pila pila, FuncionVisitante visit) {
  assert(pila != NULL);
  for (struct GNode* aux = pila->top; aux != NULL; aux = aux->next)
    visit(aux->data);
}

char* pila_toArr_char(Pila pila) {
  char* arr = malloc(sizeof(char) * pila->size+1);
  struct GNode* aux = pila->top;   
  for(int i = pila->size-1; 0 <= i; i--) {
    arr[i] = *(char*)aux->data;
    aux = aux->next;
  }
  arr[pila->size] = '\0';
  return arr;
}