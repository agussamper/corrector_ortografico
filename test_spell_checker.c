//TODO: crear .h
#include "spell_checker.h"
#include "IO.h"
#include "type_operations/int_str.h"
#include <time.h> // TODO: eliminar

void test_spell_check() {
  TablaHash dic = load_file("dictionaries/words", 1000, 100);
  Pila pila = spell_check(dic, "texts/bible.txt");
  pila_imprimir(pila, (FuncionVisitante)int_str_visit);
  pila_destruir(pila, (FuncionDestructora)int_str_free);
  tablahash_destruir(dic);  
}

void test_print_suggestions() {
  TablaHash dic = load_file("dictionaries/es1.txt", 1000, 100);
  print_suggestions(dic, "texts/texto.txt");
  tablahash_destruir(dic);  
}

//TODO: borrar main
int main() {
  //test_spell_check();
  clock_t t = clock();
  test_print_suggestions();  
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  printf("test_create_suggestions took %f seconds to execute\n", time_taken);
}