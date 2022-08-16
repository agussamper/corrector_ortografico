#ifndef __STRFUNC_H__
#define __STRFUNC_H__

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve 
 */
char* str_cpy(const char* string);

/**
 * Imprime el string pasado por argumentos
 */
void str_visit(const char* str);

/**
 * Destruye el valor al que apunte el puntero
 * pasado por argumentos 
 */
void str_free(char *string);

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned str_KRHash(const char *s);

#endif