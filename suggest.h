#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "pila/pila.h"
#include "hashtable/tablahash.h"
#include "type_operations/char_str.h"

//TODO: agregar explicacion en comentarios sobre para que sive mem

/**
 * Intercambia cada par de caracteres adyacentes de str. Agrega
 * en inDic las palabras que luego de la modificación en str
 * se encuentran en el diccionario y en strObt todas las palabras
 * obtenidas.
 */
void technique1(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Inserta cada letra de la 'A' a la 'Z' en cualquier posición
 * de str. Agrega en inDic las palabras que luego de la
 * modificación se encuentran en el diccionario y en strObt
 * todas las palabras obtenidas.
 * 
 */
void technique2(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Elimina cada caracter de str. Agrega en inDic las palabras
 * que luego de la modificación se encuentran en el diccionario
 * y en strObt todas las palabras obtenidas.
 */
void technique3(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Reemplaza cada caracter de la palabra con cada letra de la 'A'
 * a la 'z'. Agrega en inDic las palabras que luego de la modificación
 * se encuentran en el diccionario y en strObt todas las palabras
 * obtenidas.
 */
void technique4(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Spara str en un par de palabras agregando un espacio entre cada
 * par de caracteres adyacentes en la palabra.
 * Agrega en inDic las palabras que luego de la modificación
 * se encuentran en el diccionario.
 */
void technique5(Pila inDic, TablaHash dic, TablaHash mem, char* str);

Pila create_suggestions(TablaHash dic, char* str);

#endif