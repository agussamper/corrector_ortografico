#ifndef __INT_STR_H__
#define __INT_STR_H__

typedef struct {
  char *str;
  unsigned num;
} Int_str;

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve 
 */
Int_str* int_str_cpy(Int_str* istr);

/**
 * Retorna la variable pasada por argumentos
 */
Int_str* int_str_return(Int_str* istr);

/**
 * Imprime la información en el dato
 * pasado por parámetros 
 */
void int_str_visit(Int_str* istr);

/**
 * Libera los datos en istr
 */
void int_str_free(Int_str* istr);

#endif