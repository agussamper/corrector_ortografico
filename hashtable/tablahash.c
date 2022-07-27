#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  unsigned dist; // Indica la distancia del slot al que fue hasheado el dato   
  void *dato;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].dist = 0;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      tabla->destr(tabla->elems[idx].dato);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

void tablahash_insertar(TablaHash tabla, void *dato) { 
  
  // Si el factor de carga es mayor a 0.7 se redimensiona la tabla
  if (tabla->numElems*10/tabla->capacidad >= 7)
    tablahash_rehash(tabla);    
  
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;  

  unsigned dist = 0;
  
  void *copiaDato = tabla->copia(dato);

  while(1) {    
    // Insertar el dato si la casilla estaba libre.
    if (tabla->elems[idx].dato == NULL) {
      tabla->numElems++;
      tabla->elems[idx].dato = copiaDato;
      tabla->elems[idx].dist = dist;
      return;
    }
    // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
    else if (tabla->comp(tabla->elems[idx].dato, copiaDato) == 0) {
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = copiaDato;
      return;
    }
    /* Intercambio lo que hay en la tabla por el dato a ingresar
     * si la distancia de lo que hay en la tabla es menor que la distancia
     * que esta teniendo el dato a ingresar de su slot
     */
    else if (tabla->elems[idx].dist < dist) {
      void* aux = tabla->elems[idx].dato;
      tabla->elems[idx].dato = copiaDato;
      copiaDato = aux;
      unsigned distAnt = tabla->elems[idx].dist;
      tabla->elems[idx].dist = dist;
      dist = distAnt;
    }    
    dist++;
    idx = (idx + 1) % tabla->capacidad;
  }
}

//TODO: OPTIMIZAR
void tablahash_rehash(TablaHash tabla) {
  CasillaHash* aux = malloc(sizeof(CasillaHash) * tabla->capacidad);
  assert(aux != NULL);
  for(int i = 0; i < tabla->capacidad; i++) {
    if(tabla->elems[i].dato != NULL)
      aux[i].dato = tabla->elems[i].dato;
    else
      aux[i].dato = NULL;
  }

  free(tabla->elems);
  tabla->elems = malloc(sizeof(CasillaHash) * tabla->capacidad * 2);
  assert(tabla->elems != NULL);
  int numElemsAnt = tabla->numElems;
  int capacidadAnt = tabla->capacidad;
  tabla->capacidad = tabla->capacidad * 2;
  tabla->numElems = 0;
  for(int i = 0; i < tabla->capacidad; i++) {
    tabla->elems[i].dato = NULL;
    tabla->elems[i].dist = 0;
  }
  for(int i = 0; i < capacidadAnt; i++) {
    if(aux[i].dato != NULL) {
      tablahash_insertar(tabla, aux[i].dato);
      tabla->destr(aux[i].dato);
    }
  }
  free(aux);
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned distance = 0;
  do {
    // Retornar NULL si la casilla estaba vacia.
    if (tabla->elems[idx].dato == NULL)
      return NULL;
    // Retornar el dato de la casilla si hay concidencia.
    else if (tabla->comp(tabla->elems[idx].dato, dato) == 0)
      return tabla->elems[idx].dato;
    
    idx = (idx + 1) % tabla->capacidad;
    distance++;
    
  } while (distance <= tabla->elems[idx].dist);

  return NULL;
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  unsigned distance = 0;

  do {
    // Retornar si la casilla estaba vacia.
    if (tabla->elems[idx].dato == NULL)
      return;
    // Vaciar la casilla si hay coincidencia.
    else if (tabla->comp(tabla->elems[idx].dato, dato) == 0) {
      tabla->numElems--;
      tabla->destr(tabla->elems[idx].dato);
      tabla->elems[idx].dato = NULL;
      tabla->elems[idx].dist = 0;

      idx = (idx + 1) % tabla->capacidad;
      while (tabla->elems[idx].dist > 0) {
        tabla->elems[(idx - 1) % tabla->capacidad].dato =
          tabla->elems[idx].dato;
        tabla->elems[(idx - 1) % tabla->capacidad].dist =
          tabla->elems[idx].dist - 1;
        tabla->destr(tabla->elems[idx].dato);
        tabla->elems[idx].dato = NULL;
        tabla->elems[idx].dist = 0;
        idx = (idx + 1) % tabla->capacidad;
      } 
      return;
    }
    distance++;
    idx = (idx + 1) % tabla->capacidad;
  } while (distance <= tabla->elems[idx].dist);
}
