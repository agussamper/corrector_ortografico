#include <stdlib.h>
#include <stdio.h>
#include "char_func.h"

char* char_copy(char* dato) {  
  char* copy = malloc(sizeof(char));
  *copy = *dato;
  return copy;
}

void char_free(char *dato) {
  free(dato);
}

void char_visit(char* dato) {
  printf("%c \n", *dato);
}

int char_fcmp(char *dato1, char *dato2) {
  return *(unsigned char*)dato1 - *(unsigned char*)dato2;
}