#include "str_len_int.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Str_len_int* str_len_int_cpy(Str_len_int* strli) {
  Str_len_int* strli_cpy = malloc(sizeof(Str_len_int));
  strli_cpy->str = malloc(sizeof(char) * (strli->len_str + 1));
  strcpy(strli_cpy->str, strli->str);
  strli_cpy->len_str = strli->len_str;
  strli_cpy->num = strli->num;  
  return strli_cpy;
}

Str_len_int* str_len_int_return(Str_len_int* strli) {
  return strli;
}

void str_len_int_visit(Str_len_int* strli) {
  printf("str: %s, len_str: %d, num: %d\n",
    strli->str, strli->len_str, strli->num);
}

void str_len_int_free(Str_len_int* strli) {
  free(strli->str);
  free(strli);
}
