#include "utils.h"
//#include <stdio.h> //TODO: eliminar
/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}

/*unsigned KRHash(char *s) {
  unsigned hashval = 0;
  for(int i = 0; *s != '\0'; s++) {
    hashval += *s * i;
    i++; 
  }
  return hashval;
}*/

/*int main() { //TODO: borrar
  printf("aaronico:%u\n", KRHash("aaronico"));
  printf("aaronioc:%u\n", KRHash("aaronioc"));
  printf("aaronicos:%u\n", KRHash("aaronicos"));
  printf("aaronica:%u\n", KRHash("aaronica"));
  printf("aaronicas:%u\n", KRHash("aaronicas"));
  printf("aaronita:%u\n", KRHash("aaronita"));
  printf("aaronitas:%u\n", KRHash("aaronitas"));  
}*/