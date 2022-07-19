#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void* int_cpy(void* dato) {
  int* copiaDato = malloc(sizeof(int));
  assert(copiaDato);
  *copiaDato = *(int*)dato;
  return copiaDato;
}

int int_fcmp(void* dato1, void* dato2) {
  return *(int*)dato1 - *(int*)dato2;
}

void int_visit(void* dato) {
  printf("%d ", *(int*)dato);
}

void int_destruir(void *a) {
  free(a);
}
