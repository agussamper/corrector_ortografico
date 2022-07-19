#ifndef __INF_STR_H__
#define __INF_STR_H__

typedef struct {
  char *word;
  unsigned line;
} Inf_str;

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve 
 */
Inf_str* inf_str_cpy(Inf_str* istr);

/**
 * Imprime la información en el dato
 * pasado por parámetros 
 */
void inf_str_visit(Inf_str* istr);

/**
 * Libera los datos en istr
 */
void inf_str_free(Inf_str* istr);

#endif