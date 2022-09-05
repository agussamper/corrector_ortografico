#include "spell_checker.h"
#include "IO.h"
#include "suggest.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void aux_spell_check(TrieNode dic, char* buf,
    unsigned count, unsigned line, FILE* fileOut) {
  if(count > 0) {
    buf[count] = '\0';
    if(checkPresent(dic, buf) == 0) {
      fprintf(fileOut, "Linea %d, '%s' no esta en el diccionario.\n", line, buf);
      create_suggestions(dic, buf, fileOut);
    }
  }
}

void spell_check(TrieNode dic, const char* pathIn, const char* pathOut) {
  FILE* fileIn = open_file(pathIn, "r");
  FILE* fileOut = open_file(pathOut, "w");

  char buf[50];
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(fileIn)) != EOF) {
    c = tolower(c); 
    if('a' <= c && c <= 'z') {
      buf[count] = c;
      count++;
    } else {
      aux_spell_check(dic, buf, count, line, fileOut);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  aux_spell_check(dic, buf, count, line, fileOut);
  fclose(fileOut);
  fclose(fileIn);
}