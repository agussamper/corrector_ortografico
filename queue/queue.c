#include "queue.h"
#include <stdlib.h>
#include <assert.h>

struct _Queue {  
  struct GNode *front;
  struct GNode *rear;
  int size;
};

struct GNode {
  void *data;
  struct GNode *next;
};

Queue queue_crear() {
  Queue newq = malloc(sizeof(struct _Queue));
  assert(newq);
  newq->front = NULL;
  newq->rear = NULL;
  newq->size = 0;
  return newq;
}

void queue_destruir(Queue queue, FuncionDestructora destruir) {
  assert(queue != NULL);
  struct GNode* nodeToDelete;
  while (queue->front != NULL) {
    nodeToDelete = queue->front;
    queue->front = queue->front->next;
    destruir(nodeToDelete->data);
    free(nodeToDelete);
  }
  free(queue);
}

int queue_vacia(Queue queue) {
  assert(queue != NULL);
  return queue->front == NULL;
}

void queue_enqueue(Queue queue, FuncionCopia cpy, void* dato) {
  assert(queue != NULL);
  struct GNode *newNode = malloc(sizeof(struct GNode));
  assert(newNode != NULL);
  newNode->next = NULL;
  newNode->data = cpy(dato);

  if(queue_vacia(queue)) {
    queue->rear = newNode;
    queue->front = queue->rear;
  } else {
    queue->rear->next = newNode;
    queue->rear = queue->rear->next;
  }
  queue->size++;
}

void queue_dequeue(Queue queue, FuncionDestructora destruir) {
  assert(queue != NULL);
  if(!queue_vacia(queue)) {
    struct GNode* toDelete = queue->front;
    queue->front = queue->front->next;
    if(queue->front == NULL)
      queue->rear = queue->front;
    destruir(toDelete->data);
    free(toDelete);
    queue->size--;
  }
}

void queue_recorrer(Queue queue, FuncionVisitante visit) {
  assert(queue != NULL);
  for (struct GNode* aux = queue->front; aux != NULL; aux = aux->next)
    visit(aux->data);
}

void* queue_front(Queue queue) {
  assert(queue != NULL);
  if(queue->front == NULL)
    return NULL;
  return queue->front->data;
}

void* queue_rear(Queue queue) {
  assert(queue != NULL);
  if(queue->rear == NULL)
    return NULL;
  return queue->rear->data;
}

unsigned queue_size(Queue queue) {
  assert(queue != NULL);
  return queue->size;
}