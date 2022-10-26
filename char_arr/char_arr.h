#ifndef __CHAR_ARR_H__
#define __CHAR_ARR_H__

typedef struct _Char_arr *Char_arr;

// Inicializa el arreglo de caracteres con la
// capacidad inicial especificada por argumentos
Char_arr char_arr_init(int size);

// Destruye el arreglo
void char_arr_destroy(Char_arr arr);

// Escribe el char en la posición indicada del arreglo
void char_arr_write(Char_arr arr, unsigned pos, char ch);

// Devuelve la capacidad del arreglo
unsigned char_arr_size(Char_arr arr);

// Ajusta el ramaño deñ arreglo. Si la nueva capacidad es menor,
// el contenido es truncado
void char_arr_resize(Char_arr arr, unsigned size);

// Devuelve un puntero al string guardado en _Char_str
char* char_arr_getStr();

#endif