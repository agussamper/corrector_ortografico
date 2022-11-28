#ifndef __Str_len_int_H__
#define __Str_len_int_H__

typedef struct {
  char *str;
  unsigned len_str;
  unsigned num;
} Str_len_int;

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve.
 * Antes de llamar a la funcion asegurarse que
 * strli->len_str tenga la longitud del string
 */
Str_len_int* str_len_int_cpy(Str_len_int* strli);

/**
 * Retorna la variable pasada por argumentos
 */
Str_len_int* str_len_int_return(Str_len_int* strli);

/**
 * Imprime la información en el dato
 * pasado por parámetros 
 */
void str_len_int_visit(Str_len_int* strli);

/**
 * Libera los datos en strli
 */
void str_len_int_free(Str_len_int* strli);

#endif