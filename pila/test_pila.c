#include "test_pila.h"
#include "pila.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../type_operations/int_func.h"
#include "../type_operations/char_func.h"

void test_pila_crear() {
  Pila pila = pila_crear();
  assert(pila_es_vacia(pila));
  assert(pila_size(pila) == 0);
  pila_destruir(pila, int_destruir);
}

void test_pila_es_vacia() {
  Pila pila = pila_crear();
  assert(pila_es_vacia(pila));

  int nums[] = {0, 1, 2, 3};
  pila_apilar(pila, nums, int_cpy);
  assert(pila_es_vacia(pila) == 0);

  pila_desapilar(pila, int_destruir);
  assert(pila_es_vacia(pila));

  for(int i = 0; i < 4; i++)
    pila_apilar(pila, nums + i, int_cpy);
  
  assert(pila_es_vacia(pila) == 0);

  pila_destruir(pila, int_destruir);
}

void* test_pila_tope() {
  Pila pila = pila_crear();
  int nums[] = {0, 1, 2, 3};
  for(int i = 0; i < 4; i++)
    pila_apilar(pila, nums + i, int_cpy);

  for(int i = 3; -1 < i; i--) {
    assert(*(int*)pila_tope(pila) == nums[i]);
    pila_desapilar(pila, int_destruir);
  }
  pila_destruir(pila, int_destruir);
}

void test_pila_size() {
  Pila pila = pila_crear();
  assert(pila_size(pila) == 0);
  int nums[] = {0, 1, 2, 3};  
  for(int i = 0; i < 4; i++) {
    pila_apilar(pila, nums + i, int_cpy);
    assert(pila_size(pila) == i + 1);
  }
  for(int i = 3; -1 < i; i--) {
    pila_desapilar(pila, int_destruir);
    assert(pila_size(pila) == i);
  }
  pila_destruir(pila, int_destruir);
} 

void test_pila_apilar() {
  Pila pila = pila_crear();
  int nums[] = {0,1,2,3,4,5,6,7,8,9,10};
  for (int i = 0; i < 11; i++) {
    pila_apilar(pila, nums + i, int_cpy);
    assert(pila_size(pila) == i + 1);
    if(!pila_es_vacia(pila))
      assert(*(int*)pila_tope(pila) == nums[i]);      
  }
  pila_desapilar(pila, int_destruir);
  pila_desapilar(pila, int_destruir);
  pila_apilar(pila, nums, int_cpy);
  assert(*(int*)pila_tope(pila) == nums[0]);
  assert(pila_size(pila) == 10);

  pila_destruir(pila, int_destruir);
}


void test_pila_desapilar() {
  Pila pila = pila_crear();
  int nums[] = {0,1,2,3,4,5,6,7,8,9,10};
  for (int i = 0; i < 11; i++)
    pila_apilar(pila, nums + i, int_cpy);

  for(int i = 10; -1 < i; i--) {
    pila_desapilar(pila, int_destruir);
    assert(pila_size(pila) == i);
    if(!pila_es_vacia(pila))
      assert(*(int*)pila_tope(pila) == nums[i-1]);
  }
  pila_apilar(pila, nums, int_cpy);
  pila_apilar(pila, nums + 1, int_cpy);
  pila_desapilar(pila,int_destruir);
  assert(*(int*)pila_tope(pila) == 0);
  assert(pila_size(pila) == 1);

  pila_destruir(pila, int_destruir);
}

void test_pila_toArr_char() {
  Pila pila = pila_crear();
  for(int i = 48; i < 58; i++) {
    char c = i;
    pila_apilar(pila, &c, (FuncionCopia)char_copy);
  }
  char* arr = pila_toArr_char(pila);  
  pila_destruir(pila, (FuncionDestructora)char_free);
  int j = 48;
  for(int i = 0; i < 10; i++) { 
    assert(arr[i] == j);
    j++;
  }
  free(arr);
}

void test_pila() {
  test_pila_crear();
  test_pila_es_vacia();
  test_pila_tope();
  test_pila_size();
  test_pila_apilar();
  test_pila_desapilar();
  test_pila_toArr_char();
}

int main() {
  test_pila();
}