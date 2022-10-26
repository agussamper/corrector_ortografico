#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "queue/queue.h"
#include "hashtable/tablahash.h"
#include "trie/trie.h"
#include "type_operations/int_str.h"
#include <stdio.h>

/**
 * Dado el número de sugerencias encontradas, un string y un archivo
 * escribe en el archivo la sugerencia la sugerencia pasada por argumento
 * dandole un formato de salida dependiendo el número de sugerencias
 * ya escritas
 */
void write_suggestion(unsigned *num_suggestions, char* suggestion, FILE *file);

/**
 * Verifica si el dato en cstr->str es una sugerencia válida. Si
 * lo es la imprime en pantalla y aumenta en 1 suggestions. 
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void checkSuggestion(unsigned *suggestions, Queue strsObtained, 
                    TrieNode dic, TablaHash mem, Int_str* istr, FILE *file);

/**
 * Intercambia cada par de caracteres adyacentes de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * unsigned str_len: longitud del string en istr->str
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void technique1(unsigned *suggestions, Queue strsObtained,
                TrieNode dic, TablaHash mem, Int_str* istr,
                unsigned str_len, FILE *file);

/**
 * Inserta cada letra de la 'A' a la 'Z' en cualquier posición
 * de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * unsigned str_len: longitud del string en istr->str
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void technique2(unsigned *suggestions, Queue strsObtained,
                TrieNode dic, TablaHash mem, Int_str* istr,
                unsigned str_len, FILE *file);

/**
 * Elimina cada caracter de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * unsigned str_len: longitud del string en istr->str
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void technique3(unsigned *suggestions, Queue strsObtained,
                TrieNode dic, TablaHash mem, Int_str* istr,
                unsigned str_len, FILE *file);

/**
 * Reemplaza cada caracter de cstr->str con cada letra de la 'A'
 * a la 'z'.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void technique4(unsigned *suggestions, Queue strsObtained,
                TrieNode dic, TablaHash mem, Int_str* istr,
                FILE *file);


/**
 * Separa str en un par de palabras agregando un espacio entre cada
 * par de caracteres adyacentes en la palabra.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned *suggestions: Guarda la cantidad de sugerencias encontradas
 * TrieNode<char*> dic: Diccionario.
 * TablaHash<char*> mem: Guarda todas las sugerencias encontradas y
 * los strings agregados strObt.
 * char* str: String que se quiere modificar.
 * unsigned str_len: longitud del string en str
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void technique5(unsigned *suggestions, TrieNode dic, TablaHash mem, 
                char* str, unsigned str_len, FILE* file);

/**
 * Dado un diccionario, una palabra y un archivo, escribe en file
 * sugerencias para str que se obtienen de aplicar las 5 técnicas.
 * TrieNode dic: Diccionario
 * char* str: string al que se le quiere encontrar sugerencias
 * FILE *file: Archivo donde se escriben las sugerencias
 */
void create_suggestions(TrieNode dic, char* str, FILE *file);

#endif