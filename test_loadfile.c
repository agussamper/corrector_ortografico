#include "loadfile.h"
#include <assert.h>
#include <time.h>

void test_load_file() {
  clock_t t = clock();


  TablaHash th = load_file("es1.txt", 100000, 100);
  printf("Tabla cargada\n");

  /*FILE* f = open_file("es1.txt", "r");
  char buf[100];
  printf("\nPalabras en el diccionario:'\n'");
  while(fgets(buf, 100, f)) {
    size_t slen = strlen(buf); 
    buf[--slen] = '\0';
    printf("%s'\n'", buf);
    assert(tablahash_buscar(th, buf));
  }*/
  tablahash_destruir(th);

  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  printf("The program took %f seconds to execute\n", time_taken);
}

int main() {
  test_load_file();
  return 0;
}