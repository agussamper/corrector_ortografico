#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "queue/queue.h"
#include "hashtable/tablahash.h"
#include "type_operations/char_str.h"

/**
 * Dado el número de sugerencias encontradas y un string le da un 
 * formato de salida al string y además aumenta num_suggestions en
 * una unidad
 */
void print_suggestion(unsigned *num_suggestions, char* suggestion);

/**
 * Verifica si el dato en cstr->str es una sugerencia válida. Si
 * lo es la imprime en pantalla y aumenta en 1 suggestions. 
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void checkSuggestion(unsigned *suggestions, Queue strsObtained, 
                    TablaHash dic, TablaHash mem, Char_str* cstr);

/**
 * Intercambia cada par de caracteres adyacentes de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique1(unsigned *suggestions, Queue strsObtained,
                TablaHash dic, TablaHash mem, Char_str* cstr);

/**
 * Inserta cada letra de la 'A' a la 'Z' en cualquier posición
 * de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique2(unsigned *suggestions, Queue strsObtained,
                TablaHash dic, TablaHash mem, Char_str* cstr);

/**
 * Elimina cada caracter de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique3(unsigned *suggestions, Queue strsObtained,
                TablaHash dic, TablaHash mem, Char_str* cstr);

/**
 * Reemplaza cada caracter de cstr->str con cada letra de la 'A'
 * a la 'z'.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Char_str* cstr: Estructura que guarda un String y un dato de
 * tipo char el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique4(unsigned *suggestions, Queue strsObtained,
                TablaHash dic, TablaHash mem, Char_str* cstr);


/**
 * Separa str en un par de palabras agregando un espacio entre cada
 * par de caracteres adyacentes en la palabra.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned *suggestions: Guarda la cantidad de sugerencias encontradas
 * TablaHash<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * char* str: String que se quiere modificar.
 */
void technique5(unsigned *suggestions, TablaHash dic, TablaHash mem, char* str);

/**
 * Dado un diccionario y una palabra, devuelve una pila con strings
 * similiares a str que se encuentran en el diccionario y se obtienen
 * aplicando las 5 técnicas.
 * TablaHash<char*> dic: Diccionario
 * char* str: string al que se le quiere encontrar sugerencias
 */
void create_suggestions(TablaHash dic, char* str);

#endif