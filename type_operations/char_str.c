#include "char_str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Char_str* char_str_cpy(Char_str* cstr) {
  Char_str* cstr_cpy = malloc(sizeof(Char_str));
  cstr_cpy->str = malloc(sizeof(char) * (strlen(cstr->str) + 1));
  strcpy(cstr_cpy->str, cstr->str);
  cstr_cpy->ch = cstr->ch;  
  return cstr_cpy;
}

Char_str* char_str_return(Char_str* cstr) {
  return cstr;
}

void char_str_visit(Char_str* cstr) {
  printf("palabra: %s, num: %c", cstr->str, cstr->ch);
  puts("");
}

void char_str_free(Char_str* cstr) {
  free(cstr->str);
  free(cstr);
}