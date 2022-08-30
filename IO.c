/**
 * carga el diccionario
 * 
 * usar una tabla hash para guardar el diccionario
 */
#include "IO.h"
#include "type_operations/strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

FILE* open_file(const char* path, const char* mode) {
    FILE *file = fopen(path, mode);
    assert(file != NULL);
    return file;
}

TablaHash load_file(const char* path) {
  FILE* file = open_file(path, "r");
  int bufSize = 50;
  TablaHash table = tablahash_crear(1000, (FuncionCopiadora)str_cpy,
                                   (FuncionComparadora)strcmp,
                                   (FuncionDestructora)str_free,
                                   (FuncionHash)str_KRHash);
  char buf[bufSize];
  unsigned line = 0;
  while(fgets(buf, bufSize, file)) {
    size_t slen = strlen(buf);
    buf[--slen] = '\0'; //Resto 1 a slen por el '\n'
    tablahash_insertar(table, buf);
    line++;
  }
  fclose(file);
  return table;
}