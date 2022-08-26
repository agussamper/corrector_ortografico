#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado) (void *dato);

typedef struct _Queue *Queue;

/**
 * Devuelve una cola vacia.
 */
Queue queue_crear();

/**
 * Libera la memoria de la cola.
 */
void queue_destruir(Queue queue, FuncionDestructora destruir);

/**
 * Determina si la cola es vacía.
 */
int queue_vacia(Queue queue);

/**
 * Agrega un elemento en la cola.
 */
void queue_enqueue(Queue queue, FuncionCopia cpy, void* dato);

/**
 * Elimina un elemento de la cola
 */
void queue_dequeue(Queue queue, FuncionDestructora destruir);

/**
 * Recorrido de la cola, utilizando la funcion pasada.
 */
void queue_recorrer(Queue queue, FuncionVisitante visit);

// Retorna el elemento que está al inicio de la cola
void* queue_front(Queue queue);

// Retorna el elemento que está al final de la cola
void* queue_rear(Queue queue);

unsigned queue_size(Queue queue);

#endif /* __QUEUE_H__ */
