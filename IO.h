#ifndef __IO_H__
#define __IO_H__

#include "trie/trie.h"
#include "hashtable/tablahash.h"
#include <stdio.h>
#include <string.h>

/**
 * Abre un archivo en la ruta y en el modo indicado y lo devuelve,
 * si no es posible abrir el archivo lanza un error y termina
 * la ejecución del programa 
 */
FILE* open_file(const char* path, const char* mode);

#endif