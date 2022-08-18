#ifndef __CHAR_STR_H__
#define __CHAR_STR_H__

typedef struct {
  char *str;
  char ch;
} Char_str;

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve 
 */
Char_str* char_str_cpy(Char_str* cstr);

/**
 * Retorna la variable pasada por argumentos
 */
Char_str* char_str_return(Char_str* cstr);

/**
 * Imprime la información en el dato
 * pasado por parámetros 
 */
void char_str_visit(Char_str* cstr);

/**
 * Libera los datos en cstr
 */
void char_str_free(Char_str* cstr);

#endif