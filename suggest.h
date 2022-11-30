#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "trie/trie.h"
#include <stdio.h>

/**
 * Dado un diccionario, una palabra y dos archivos, escribe en f_out
 * sugerencias para str que se obtienen de aplicar las 5 técnicas. 
 * Devuelve en un array las sugerencias encontradas
 */
char** create_suggestions(TrieNode dic, char* str, FILE *f_out);

#endif