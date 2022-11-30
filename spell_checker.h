#ifndef __SPELL_CHECKER_H__
#define __SPELL_CHECKER_H__

#include "trie/trie.h"

/**
 * Recibe una TrieNode que representa un diccionario,
 * la ruta de un archivo de texto de entrada(pathIn) y de 
 * un archivo salida(pathOut), si el archivo de salida
 * no existe lo crea.
 * Escribe en el archivo de salida hasta 5 sugerencias para las
 * palabras del archivo de entrada que no se encuentran
 * en el diccionario.
 */
void spell_check(TrieNode dic, const char* pathIn, const char* pathOut);

#endif