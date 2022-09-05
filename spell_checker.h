#ifndef __SPELL_CHECKER_H__
#define __SPELL_CHECKER_H__

#include "trie/trie.h"

/**
 * Recibe una TrieNode que representa un diccionario,
 * la ruta de un archivo de texto de entrada y de un archivo
 * salida, si el archivo de salida no existe lo crea.
 * Escribe en el archivo de salida sugerencias para las
 * palabras del archivo de entrada que no se encuentran
 * en el diccionario.
 */
void spell_check(TrieNode dic, const char* pathIn, const char* pathOut);

#endif