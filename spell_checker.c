#include "spell_checker.h"
#include "type_operations/int_str.h"
#include "type_operations/strFunc.h"
#include "IO.h"
#include "suggest.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void aux_spell_check(TablaHash dic, char* buf,
                      unsigned count, unsigned line) {
  if(count > 0) {
    buf[count] = '\0';
    if(tablahash_buscar(dic, buf) == NULL) {
      printf("Linea %d, '%s' no esta en el diccionario.\n", line, buf);
      create_suggestions(dic, buf);          
    }
  }
}

void spell_check(TablaHash dic, const char* path) {
  FILE* file = open_file(path, "r");

  char buf[50];
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(file)) != EOF) {
    c = tolower(c); 
    if('a' <= c && c <= 'z') {
      buf[count] = c;
      count++;
    } else {
      aux_spell_check(dic, buf, count, line);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  aux_spell_check(dic, buf, count, line);
  fclose(file);
}