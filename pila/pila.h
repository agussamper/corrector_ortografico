#ifndef __PILA_H__
#define __PILA_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado) (void *dato);

typedef struct _Pila *Pila;

// Crea e inicializa una nueva pila vacia
Pila pila_crear();

// Elimina la pila (Libera la memoria requerida para la misma)
void pila_destruir(Pila pila, FuncionDestructora destruir);

// Retorna 1 si la pila está vacía, y 0 en caso contrario
int pila_es_vacia(Pila pila);

// Retorna el elemento que se encuentra en el tope de la lista
// sin eliminarlo
void* pila_tope(Pila pila);

//Devuelve la cantidad de elementos de la lista 
int pila_size(Pila pila);

//Inserta un elemento en el tope de la pila
void pila_apilar(Pila pila, void *dato, FuncionCopia copiar);

// Elimina el elemento que se encuentra en el tope de la pila
void pila_desapilar(Pila pila, FuncionDestructora destroy);

// Imprime en orden los elementos de la pila
void pila_imprimir(Pila pila, FuncionVisitante visit);

/**
 * Dada una pila  de caracteres copia y devuelve su contenido en un array
 * con el orden invertido, es decir, el tope de la pila, es el último del
 * array, el segundo elemento de la pila es el penúltimo del array, etc. 
 * Ejemplo:
 * pila_toArr(pila['1','3','5','7']) -> arr['7','5','3','1'] 
 */
char* pila_toArr_char(Pila pila);

#endif /* __PILA_H__ */
