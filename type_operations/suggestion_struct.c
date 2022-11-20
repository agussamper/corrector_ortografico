#include "suggestion_struct.h"
#include "strFunc.h"
#include <string.h>
#include <stdlib.h>

Suggestion* suggestion_cpy(Suggestion* suggestion) {
  Suggestion* sugg_cpy = malloc(sizeof(Suggestion));

  sugg_cpy->word = malloc(sizeof(char) * (strlen(suggestion->word) + 1));
  strcpy(sugg_cpy->word, suggestion->word);

  int num_suggestions = suggestion->num_suggestions;
  sugg_cpy->num_suggestions = num_suggestions;

  sugg_cpy->suggestions = malloc(sizeof(char*) * num_suggestions);
  char** arr_sugg_cpy = sugg_cpy->suggestions;
  char** arr_sugg = suggestion->suggestions;
  for(int i = 0; i < num_suggestions; i++) {
    arr_sugg_cpy[i] = malloc(sizeof(char) * (strlen(arr_sugg[i])+1)); //TODO: Ver si es posible optimizar
    strcpy(arr_sugg_cpy[i], arr_sugg[i]);
  }
  return sugg_cpy;
}

int suggestion_cmp(Suggestion* sugg1, Suggestion* sugg2) {
  return strcmp(sugg1->word, sugg2->word);
}

void suggestion_free(Suggestion* suggestion) {
  free(suggestion->word);
  int num_sugg = suggestion->num_suggestions;
  char **arr_suggestions = suggestion->suggestions;
  for(int i = 0; i < num_sugg; i++)
    free(arr_suggestions[i]);
  free(suggestion->suggestions);
  free(suggestion);
}

unsigned suggestion_hash(Suggestion* suggestion) {
  return str_KRHash(suggestion->word);
}