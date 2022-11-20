#ifndef __SUGGEST_H__
#define __SUGGEST_H__

#include "queue/queue.h"
#include "trie/trie.h"
#include "type_operations/int_str.h"
#include <stdio.h>

//TODO: cambiar comentarios por agregado de archivo

/**
 * Dado el número de sugerencias encontradas, un string y un archivo
 * escribe en el archivo la sugerencia pasada por argumentos
 * dandole un formato de salida dependiendo el número de sugerencias
 * ya escritas
 */
void write_suggestion(unsigned *num_suggestions, char *suggestion,
                       FILE *f_out);

/**
 * Guarda la sugerencia pasada por parametros en suggestions, en
 *  la posicion *num_suggestion
 */
void save_suggestion(char** suggestions, unsigned *num_suggestion,
                      char* suggestion);

/**
 * Verifica si el dato en cstr->str es una sugerencia válida. Si
 * lo es la imprime en pantalla y aumenta en 1 suggestions. 
 * unsigned* num_suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void checkSuggestion(unsigned *num_suggestions, Queue strsObtained, 
                    TrieNode dic, char** suggestions, Int_str* istr, FILE* f_out);

/**
 * Intercambia cada par de caracteres adyacentes de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* num_suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique1(unsigned *num_suggestions, Queue strsObtained,
                TrieNode dic, char** suggestions, Int_str* istr, FILE* f_out);

/**
 * Inserta cada letra de la 'A' a la 'Z' en cualquier posición
 * de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* num_suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * size_t str_len: longitud del string en istr->str
 */
void technique2(unsigned *num_suggestions, Queue strsObtained,
                TrieNode dic, char** suggestions, Int_str* istr,
                size_t str_len, FILE* f_out);

/**
 * Elimina cada caracter de cstr->str.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* num_suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 * size_t str_len: longitud del string en istr->str
 */
void technique3(unsigned *num_suggestions, Queue strsObtained,
                TrieNode dic, char** suggestions, Int_str* istr,
                size_t str_len, FILE* f_out);

/**
 * Reemplaza cada caracter de cstr->str con cada letra de la 'A'
 * a la 'z'.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned* num_suggestions: Guarda la cantidad de sugerencias.
 * Queue<Char_str*> strObt: Guarda cstr->str si cstr->str
 * no se encuentra en mem y si cstr->ch es menor que 3.
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * Int_str* istr: Estructura que guarda un String y un dato de
 * tipo int el cuál indica la distancia en la que fue obtenida la
 * palabra
 */
void technique4(unsigned *num_suggestions, Queue strsObtained,
                TrieNode dic, char** suggestions, Int_str* istr, FILE* f_out);


/**
 * Separa str en un par de palabras agregando un espacio entre cada
 * par de caracteres adyacentes en la palabra.
 * Suma a suggestions la cantidad de sugerencias encontradas
 * unsigned *num_suggestions: Guarda la cantidad de sugerencias encontradas
 * TrieNode<char*> dic: Diccionario.
 * char** suggestions: Guarda las sugerencias encontradas
 * char* str: String que se quiere modificar.
 * size_t str_len: longitud del string en str
 */
void technique5(unsigned *num_suggestions, TrieNode dic, char** suggestions, 
                char* str, size_t str_len, FILE* f_out);

/**
 * Dado un diccionario, una palabra y dos archivos, escribe en f_out
 * sugerencias para str que se obtienen de aplicar las 5 técnicas. 
 * Devuelve en un array las sugerencias encontradas
 */
char** create_suggestions(TrieNode dic, char* str, FILE *f_out);

#endif