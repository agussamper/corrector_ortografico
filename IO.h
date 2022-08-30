#ifndef __IO_H__
#define __IO_H__

#include "hashtable/tablahash.h"
#include <stdio.h>
#include <string.h>

/**
 * Recibe la ruta de un archivo de texto y devuelve su contenido
 * en una tabla hash, en la cual, cada dato guardado en la tablahash
 * será lo que se encuentra en cada linea. Por ejemplo, si en la
 * primer linea se encuentra la oración "Hola agustín.", eso es lo
 * que se guardará en algún slot de la tabla.
 */
TablaHash load_file(const char* path);

/**
 * Abre un archivo en la ruta y en el modo indicado y lo devuelve,
 * si no es posible abrir el archivo lanza un error y termina
 * la ejecución del programa 
 */
FILE* open_file(const char* path, const char* mode);

#endif