#include "spell_checker.h"
#include "IO.h"
#include "suggest.h"
#include "char_arr/char_arr.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

void aux_spell_check(TrieNode dic, char* str,
    unsigned count, unsigned line, FILE* fileOut) {
  if(count > 0) {
    str[count] = '\0';
    if(trie_checkPresent(dic, str) == 0) {
      fprintf(fileOut, "Linea %d, '%s' no esta en el diccionario.\n", line, str);
      create_suggestions(dic, str, fileOut);
    }
  }
}

void spell_check(TrieNode dic, const char* pathIn, const char* pathOut) {
  FILE* fileIn = open_file(pathIn, "r");
  FILE* fileOut = open_file(pathOut, "w");

  Char_arr buf = char_arr_init(100);
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(fileIn)) != EOF) {
    c = tolower(c); 
    if('a' <= c && c <= 'z') {
      if(count > char_arr_size(buf) - 2)
        char_arr_resize(buf, char_arr_size(buf)*2);
      char_arr_write(buf, count, c);
      count++;
    } else { 
      aux_spell_check(dic, char_arr_getStr(buf), count, line, fileOut);
      if(char_arr_size(buf) > 200)
        char_arr_resize(buf, 100);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  aux_spell_check(dic, char_arr_getStr(buf), count, line, fileOut);
  char_arr_destroy(buf);
  fclose(fileOut);
  fclose(fileIn);
}