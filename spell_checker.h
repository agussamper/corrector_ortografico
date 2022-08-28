#ifndef __SPELL_CHECKER_H__
#define __SPELL_CHECKER_H__

#include "hashtable/tablahash.h"
#include "queue/queue.h"

/**
 * Recibe una tabla hash que representa un diccionario
 * y la ruta de un archivo de texto.
 * Devuelve en una cola las palabras del archivo de texto 
 * que no se encuentran en el diccionario y en la línea
 * en que se encuentran, para esto cada nodo de la cola
 * guarda una estructura de tipo inf_str. Las palabras 
 * se guardan en minúscula e ignora todos los caracteres
 * distintos a [a-zA-Z]
 */
Queue spell_check(TablaHash dic, const char* path);

//TODO: documentar
void print_suggestions(TablaHash dic, const char* path);

#endif