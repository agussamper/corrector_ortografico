#include "suggest.h"
#include "type_operations/strFunc.h"
#include "IO.h"
#include <stdio.h>

void test_technique1(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "comfrotable";

  technique1(inDic, strObt, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  printf("\nTodos los resultados:\n");
  pila_imprimir(strObt, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique2(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "comfotable";

  technique2(inDic, strObt, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  printf("\nTodos los resultados:\n");
  pila_imprimir(strObt, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique3(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "comafortable";

  technique3(inDic, strObt, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  printf("\nTodos los resultados:\n");
  pila_imprimir(strObt, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique4(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "comrortable";

  technique4(inDic, strObt, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  //printf("\nTodos los resultados:\n");
  //pila_imprimir(strObt, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique5(TablaHash dic) {
  Pila inDic = pila_crear();
  char str[] = "seeyou";

  technique5(inDic, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
}

int main() {
  TablaHash dic = load_file("dictionaries/words", 1000, 100);
  //test_technique1(dic);
  //test_technique2(dic);
  test_technique3(dic);
  //test_technique4(dic);
  //test_technique5(dic);
  tablahash_destruir(dic);
}