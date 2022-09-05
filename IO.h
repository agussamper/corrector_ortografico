#ifndef __IO_H__
#define __IO_H__

#include "trie/trie.h"
#include <stdio.h>
#include <string.h>

/**
 * Recibe la ruta de un diccionario y carga todas sus palabras
 * en una estructura de tipo TrieNode, luego devuelve la
 * estructura. Se supone que el archivo de texto en cada linea
 * solo caracteres de la a a la z y las palabras están en minúscula
 */
TrieNode load_dic(const char* path);

/**
 * Abre un archivo en la ruta y en el modo indicado y lo devuelve,
 * si no es posible abrir el archivo lanza un error y termina
 * la ejecución del programa 
 */
FILE* open_file(const char* path, const char* mode);

#endif