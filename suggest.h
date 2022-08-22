#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "pila/pila.h"
#include "hashtable/tablahash.h"
#include "type_operations/char_str.h"

/**
 * Pila<char*> inDic: Guarda cstr->str si se encuentra en
 * inDic pero no en mem
 * Pila<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda las palabras que fueron agregadas
 * en inDic y strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void addToStacks(Pila inDic, Pila strObt, TablaHash dic, 
                 TablaHash mem, Char_str* cstr);

/**
 * Intercambia cada par de caracteres adyacentes de cstr->str.
 * Pila<char*> inDic: Guarda las palabras que luego de la
 * modificación se encuentran en dic y además no se encuentran
 * en mem.
 * Pila<Char_str*> strObt: Guarda todas los strings que son
 * obtenidos luego de la modificación a char->str que no
 * se encuentran en mem y la distancia en que fueron obtenidos. 
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda las palabras que fueron agregadas
 * en inDic y strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique1(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Inserta cada letra de la 'A' a la 'Z' en cualquier posición
 * de cstr->str.
 * Pila<char*> inDic: Guarda las palabras que luego de la
 * modificación se encuentran en dic y además no se encuentran
 * en mem.
 * Pila<Char_str*> strObt: Guarda todas los strings que son
 * obtenidos luego de la modificación a char->str que no
 * se encuentran en mem y la distancia en que fueron obtenidos. 
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda las palabras que fueron agregadas
 * en inDic y strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */

void technique2(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Elimina cada caracter de cstr->str.
 * Pila<char*> inDic: Guarda las palabras que luego de la
 * modificación se encuentran en dic y además no se encuentran
 * en mem.
 * Pila<Char_str*> strObt: Guarda todas los strings que son
 * obtenidos luego de la modificación a char->str que no
 * se encuentran en mem y la distancia en que fueron obtenidos. 
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda las palabras que fueron agregadas
 * en inDic y strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique3(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);

/**
 * Reemplaza cada caracter de cstr->str con cada letra de la 'A'
 * a la 'z'.
 * Pila<char*> inDic: Guarda las palabras que luego de la
 * modificación se encuentran en dic y además no se encuentran
 * en mem.
 * Pila<Char_str*> strObt: Guarda todas los string que son
 * obtenidos luego de la modificación a char->str que no
 * se encuentran en mem y la distancia en que fueron obtenidos. 
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda las palabras que fueron agregadas
 * en inDic y strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique4(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr);


/**
 * Separa str en un par de palabras agregando un espacio entre cada
 * par de caracteres adyacentes en la palabra.
 * Pila<char*> inDic: Guarda los strings que luego de la
 * modificación se encuentran en dic y además no se encuentran
 * en mem.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda los strings que fueron agregados
 * en inDic y strObt.
 */
void technique5(Pila inDic, TablaHash dic, TablaHash mem, char* str);

/**
 * Dado un diccionario y una palabra, devuelve una pila con strings
 * similiares a str que se encuentran en el diccionario y se obtienen
 * aplicando las 5 técnicas.
 * TablaHash<char*>
 */
Pila create_suggestions(TablaHash dic, char* str);

#endif