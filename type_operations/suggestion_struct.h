#ifndef __SUGGESTION_STRUCT_H__
#define __SUGGESTION_STRUCT_H__

typedef struct {
  char* word;
  int num_suggestions;
  char** suggestions;
} Suggestion;

// Devuelve una copia de la estructura pasada por parametros
Suggestion* suggestion_cpy(Suggestion* suggestion);

/**
 * Compara el sugg1->word con sugg2->word usando
 * strcmp y devuelve el resultao de ello 
 */
int suggestion_cmp(Suggestion* sugg1, Suggestion* sugg2);

// Libera la memoria de la sugerencia
void suggestion_free(Suggestion* suggestion);

// Hashea suggestion, para esto sólo se tiene en cuenta
// suggestion->word
unsigned suggestion_hash(Suggestion* suggestion);

#endif