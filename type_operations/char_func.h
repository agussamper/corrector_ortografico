#ifndef __CHAR_FUNC_H__
#define __CHAR_FUNC_H__

/**
 * Copia el dato pasado por argumentos
 * y lo devuelve 
 */
char* char_copy(char* dato);

/**
 * Retorna un entero negativo si el primer argumento es menor
 * que el segundo, 0 si son iguales y un entero positivo en
 * caso contrario
 */
int char_fcmp(char* dato1, char* dato2);


//Imprime el valor del dato pasado por argumentos 
void char_visit(char* dato);

/**
 * Destruye el valor al que apunte el puntero
 * pasado por argumentos 
 */
void char_free(char *a);

#endif