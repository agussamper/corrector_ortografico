// verifica si las palabras insertadas en 
// la entrada son correctas

#include "spell_checker.h"
#include "type_operations/inf_str.h"
#include "IO.h"
#include <stdio.h>
#include <ctype.h>

Pila spell_check(TablaHash dictionary, const char* path) {
  FILE* file = open_file(path, "r");
  Pila pila = pila_crear();

  char buf[100];
  char c;
  unsigned count = 0;
  unsigned line = 1;
  Inf_str* istr;
  while((c = fgetc(file)) != EOF) {
    c = tolower(c); 
    if(97 <= c && c <= 122) {
      buf[count] = c;
      count++;
    } else {
      buf[count] = '\0';
      if(tablahash_buscar(dictionary, buf) == NULL && count > 0) {
        istr->word = buf;
        istr->line = line;      
        pila_apilar(pila, istr, (FuncionCopia)inf_str_cpy);
      }
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  fclose(file);
  return pila;
}