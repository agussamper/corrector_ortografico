#include "strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

char* str_cpy(const char* string) {
  char* copy = malloc(sizeof(char) * (strlen(string) + 1));
  assert(copy);
  strcpy(copy, string);
  return copy;
}

void str_visit(const char* str) {
  printf("%s", str);
  puts("");
}

void str_free(char* string) {
  free(string);
}

unsigned str_KRHash(const char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}