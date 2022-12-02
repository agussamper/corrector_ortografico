#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "trie/trie.h"
#include <stdio.h>

/**
 * Dado un diccionario, una palabra y dos archivos, escribe en f_out
 * sugerencias para str que se obtienen de aplicar las 5 técnicas. 
 * Devuelve un array de a lo sumo 5 sugerencias, el mismo está
 * ordenado por la distancia en que fué encontrada cada palabra,
 * ejemplo:
 * Supongamos que "hola" y "ho la" son las únicas palabras del
 * diccionario y pasamos como argumento la cadena "ohla", la
 * función devolvería el siguiente array:
 * ["hola", "ho la", NULL, NULL, NULL]
 * donde "hola" está a distancia 1 y "ho la" a distancia 2.
 */
char** create_suggestions(TrieNode dic, char* str, FILE *f_out);

#endif