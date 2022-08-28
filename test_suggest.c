#include "suggest.h"
#include "type_operations/strFunc.h"
#include "type_operations/char_str.h"
#include "IO.h"
#include <stdio.h>
#include <time.h>

//TODO: Crear tests

/*TablaHash create_mem() {
  return tablahash_crear(100, (FuncionCopiadora)str_cpy,
                         (FuncionComparadora)strcmp,
                         (FuncionDestructora)str_free,
                         (FuncionHash)str_KRHash);
}

void test_technique1(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "amitsoso";
  Char_str* cstr;
  cstr->str = str;
  cstr->ch = 0;
  technique1(inDic, strObt, dic, create_mem(), str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique2(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "amitoso";

  technique2(inDic, strObt, dic, create_mem(), str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique3(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "amistoaso";

  technique3(inDic, strObt, dic, create_mem(), str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}

void test_technique4(TablaHash dic) {
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  char str[] = "raoido";

  technique4(inDic, strObt, dic, create_mem(), str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
  pila_destruir(strObt, (FuncionDestructora)str_free);  
}
*/
/*void test_technique5(TablaHash dic) {
  Pila inDic = pila_crear();
  char str[] = "porque";

  technique5(inDic, dic, str);

  printf("Resultados en diccionario:\n");
  pila_imprimir(inDic, (FuncionVisitante)str_visit);

  pila_destruir(inDic, (FuncionDestructora)str_free);
}*/

void test_create_suggestions(TablaHash dic) {
  //Pila suggestions = create_suggestions(dic, "aplauos");
  //Pila suggestions = create_suggestions(dic, "adormecidosmurcielagos");
  create_suggestions(dic, "holasi");
}

int main() {  
  TablaHash dic = load_file("dictionaries/es1.txt", 1000, 100);
  /*test_technique1(dic);
  test_technique2(dic);
  test_technique3(dic);
  test_technique4(dic);
  test_technique5(dic);*/

  clock_t t = clock();

  test_create_suggestions(dic);
  
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  printf("test_create_suggestions took %f seconds to execute\n", time_taken);

  tablahash_destruir(dic);  
}