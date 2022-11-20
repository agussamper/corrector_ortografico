#include "int_str.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Int_str* int_str_cpy(Int_str* istr) {
  Int_str* istr_cpy = malloc(sizeof(Int_str));
  istr_cpy->str = malloc(sizeof(char) * (strlen(istr->str) + 1)); //TODO: Ver si se puede optimizar para no usar strlen o solo usarlo una vez una opcion es guardar la longitud en la misma estructura
  strcpy(istr_cpy->str, istr->str);
  istr_cpy->num = istr->num;  
  return istr_cpy;
}

Int_str* int_str_return(Int_str* istr) {
  return istr;
}

void int_str_visit(Int_str* istr) {
  printf("str: %s, num: %d", istr->str, istr->num);
  puts("");
}

void int_str_free(Int_str* istr) {
  free(istr->str);
  free(istr);
}
