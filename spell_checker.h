#ifndef __SPELL_CHECKER_H__
#define __SPELL_CHECKER_H__

#include "hashtable/tablahash.h"

/**
 * Recibe una tabla hash que representa un diccionario,
 * la ruta de un archivo de texto de entrada y de un archivo
 * salida, si el archivo de salida no existe lo crea.
 * Escribe en el archivo de salida sugerencias para las
 * palabras del archivo de entrada que no se encuentran
 * en el diccionario.
 */
void spell_check(TablaHash dic, const char* pathIn, const char* pathOut);

#endif