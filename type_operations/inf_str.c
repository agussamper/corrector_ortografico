#include "inf_str.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Inf_str* inf_str_cpy(Inf_str* istr) {
  Inf_str* istr_cpy = malloc(sizeof(Inf_str));
  istr_cpy->word = malloc(sizeof(char) * (strlen(istr->word) + 1));
  strcpy(istr_cpy->word, istr->word);
  istr_cpy->line = istr->line;  
  return istr_cpy;
}

Inf_str* inf_str_return(Inf_str* istr) {
  return istr;
}

void inf_str_visit(Inf_str* istr) {
  printf("palabra: %s, linea: %d", istr->word, istr->line);
  puts("");
}

void inf_str_free(Inf_str* istr) {
  free(istr->word);
  free(istr);
}