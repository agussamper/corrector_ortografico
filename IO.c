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

TablaHash load_file(const char* path, const unsigned initialValue,
                     const size_t maxLength) {
  FILE* file = open_file(path, "r");

  TablaHash table = tablahash_crear(initialValue, (FuncionCopiadora)str_cpy,
                                   (FuncionComparadora)strcmp,
                                   (FuncionDestructora)str_free,
                                   (FuncionHash)str_KRHash);
  char buf[maxLength];
  unsigned line = 0;
  while(fgets(buf, maxLength, file)) {
    size_t slen = strlen(buf); 
    if (slen - 1 > maxLength) { // Resto 1 ya que no cuento el '\n'
      //TODO: cambiar printf por perror(s)
      printf("Texto en línea %d con longitud %d, supera la longitud máxima de %d",
              line, slen, maxLength);
      exit(1);
    }
    buf[--slen] = '\0';
    tablahash_insertar(table, buf);
    line++;
  }
  fclose(file);
  return table;
}