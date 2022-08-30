//TODO: crear .h
#include "spell_checker.h"
#include "IO.h"
#include "type_operations/int_str.h"
#include <time.h> // TODO: eliminar

void test_spell_check() {
  TablaHash dic = load_file("dictionaries/es1.txt", 1000, 100);
  spell_check(dic, "texts/large_line.txt");
  tablahash_destruir(dic);  
}

//TODO: borrar main
int main() {
  //test_spell_check();
  clock_t t = clock();
  test_spell_check();  
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  printf("test_print_suggestions took %f seconds to execute\n", time_taken);
  return 0;
}
