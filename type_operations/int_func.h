#ifndef __INT_FUNC_H__
#define __INT_FUNC_H__

/**
 * Copia el dato pasado por argumentos
 * (de tipo int) y lo devuelve 
 */
void* int_cpy(void* dato);

/**
 * Retorna un entero negativo si el primer argumento es menor
 * que el segundo, 0 si son iguales y un entero positivo en
 * caso contrario
 */
int int_fcmp(void* dato1, void* dato2);


//Imprime el valor del dato pasado por argumentos 
void int_visit(void* dato);

/**
 * Destruye el valor al que apunte el puntero
 * pasado por argumentos 
 */
void int_destruir(void *a);

#endif