#include "spell_checker.h"
#include "IO.h"
#include "suggest.h"
#include "char_arr/char_arr.h"
#include "type_operations/suggestion_struct.h"
#include "type_operations/strFunc.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

// Guarda las sugerencias encontradas en f_calc_sugg
// con el formato 
// palabra, nro_sugerencias, sugerencia_1,..., sugerencia_n
void save_suggestions(FILE *f_calc_sugg, TablaHash calc_suggestions,
                       Queue misspelled_words) {
  while(!queue_vacia(misspelled_words)) {
    Suggestion sug_aux;
    sug_aux.word = queue_front(misspelled_words);  
    Suggestion* sugg = tablahash_buscar(calc_suggestions, &sug_aux);
    if(sugg->num_suggestions != 0) {
      fprintf(f_calc_sugg, "%s, %d, %s", sugg->word, sugg->num_suggestions,
                sugg->suggestions[0]);
      for(int i = 1; i < sugg->num_suggestions; i++)
        fprintf(f_calc_sugg, ", %s", sugg->suggestions[i]);      
    } else
      fprintf(f_calc_sugg, "%s, %d", sugg->word, 0);
    fprintf(f_calc_sugg, "\n");
    
    queue_dequeue(misspelled_words, (FuncionDestructora)str_free);
  }
}

void aux_get_calc_suggestions(
      Char_arr buf, int *loadedWords,
      Suggestion *suggestion,
      char** arr_suggestions,
      int *saved_suggestions) {          
  switch (*loadedWords) {
  case 0:
    suggestion->word = malloc(sizeof(char) * (strlen(char_arr_getStr(buf))+1));
    strcpy(suggestion->word, char_arr_getStr(buf));
    break;
  case 1:
    suggestion->num_suggestions = atoi(char_arr_getStr(buf));
    break;
  default:
    char *suggestion = malloc(sizeof(char) * (strlen(char_arr_getStr(buf))+1));
    strcpy(suggestion, char_arr_getStr(buf)); 
    arr_suggestions[*saved_suggestions] = suggestion;
    *saved_suggestions += 1; 
    break;
  }
  *loadedWords += 1;
}

// Obtiene del archivo calc_sugesstions.txt las sugerencias
// calculadas, las guarda en una tabla hash en estructuras
// de tipo Suggestion y devuelve la tabla hash
TablaHash get_calc_suggestions(FILE* file_calc_suggestions) {
  TablaHash calc_suggestions = tablahash_crear(500, 
                              (FuncionCopiadora)suggestion_cpy,
                              (FuncionComparadora)suggestion_cmp,
                              (FuncionDestructora)suggestion_free,
                              (FuncionHash)suggestion_hash);
  
  char c;
  int index = 0;
  int loadedWords = 0;

  Suggestion suggestion;
  suggestion.word = NULL;
  suggestion.num_suggestions = 0;
  suggestion.suggestions = NULL;

  Char_arr buf = char_arr_init(100);
  int saved_suggestions = 0;
  char *arr_suggestions[5];
  for(int i = 0; i < 5; i++)
    arr_suggestions[i] = NULL;
  while((c = fgetc(file_calc_suggestions)) != EOF) {
    if(c != '\n') {
      c = tolower(c);
      if(('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || c == ' ') {        
        char_arr_write(buf, index, c);
        index++;
      } else if(c == ',') {
        char_arr_write(buf, index, '\0');
        aux_get_calc_suggestions(
          buf, &loadedWords, &suggestion, arr_suggestions,
          &saved_suggestions);
        index = 0;
        fgetc(file_calc_suggestions);
      }
    } else {
      char_arr_write(buf, index, '\0');
      aux_get_calc_suggestions(
          buf, &loadedWords, &suggestion, arr_suggestions,
          &saved_suggestions);

      assert(suggestion.word);
      suggestion.suggestions = arr_suggestions;
      tablahash_insertar(calc_suggestions, &suggestion);

      // Reinicio variables y libero la memoria
      for(int i = 0; i < saved_suggestions; i++) {
        free(arr_suggestions[i]);
        arr_suggestions[i] = NULL;
      }
      free(suggestion.word);
      suggestion.word = NULL;
      
      index = 0;
      loadedWords = 0;
      saved_suggestions = 0;
    }
  }
  char_arr_destroy(buf);
  return calc_suggestions;
}

//TODO: add comments
int getNumSuggestions(char** suggestions) {
  if(suggestions == NULL)
    return 0;
  int i = 0;
  for(i = 0; i < 5; i++) {
    if(suggestions[i] == NULL)
      return i;
  }
  if (suggestions[i-1] != NULL)
    return 5;
  return 0;
}

void aux_spell_check(TrieNode dic, char* str,
      unsigned count, unsigned line,
      TablaHash calc_suggestions, Queue misspelled_words,
      FILE* fileOut) {
  if(count > 0) {
    str[count] = '\0';
    if(trie_checkPresent(dic, str) == 0) {
      fprintf(fileOut, "Linea %d, '%s' no esta en el diccionario.\n", line, str);
      Suggestion sugg;
      sugg.word = str;
      Suggestion* sugg_calc = tablahash_buscar(calc_suggestions, &sugg);
      if(sugg_calc != NULL) {
        if(sugg_calc->num_suggestions != 0) {
          char** suggestions = sugg_calc->suggestions;
          fprintf(fileOut, "Quizas quiso decir: %s", suggestions[0]);
          for(int i = 1; i < sugg_calc->num_suggestions; i++)
            fprintf(fileOut, ", %s", suggestions[i]);          
        } else
          fprintf(fileOut, "No se encontraron sugerencias");
        fputs("\n\n", fileOut);

      } else {
        char** suggestions = create_suggestions(dic, str, fileOut);
        //TODO: solucionar problema de carga en calc_suggestion.txt
        // Descripcion del problema:
        /* Si hay una palabra repetida en el input la guarda dos
         * veces en calc_suggestion.txt
         * Posible solucion: guardar las sugerencias ya encontradas en una tablahash
         * usar esas sugerencias para ahorrar futuras busquedas, ademas guardar
         * en una queue las palabras las palabras a las que se le buscaron sugerencias
         * y recuperar de la tabla hash las sugerencias
         */
        queue_enqueue(misspelled_words, (FuncionCopia)str_cpy, str);

        Suggestion str_suggestion;
        str_suggestion.word = str;
        str_suggestion.num_suggestions = getNumSuggestions(suggestions);
        str_suggestion.suggestions = suggestions;
        tablahash_insertar(calc_suggestions, &str_suggestion);
        if(suggestions != NULL) {
          for(int i = 0; i < str_suggestion.num_suggestions; i++)
            free(suggestions[i]);
          free(suggestions);
        }
      }
    }
  }
}

void spell_check(TrieNode dic, const char* pathIn, const char* pathOut) {
  FILE* fileIn = open_file(pathIn, "r");
  FILE* fileOut = open_file(pathOut, "w");

  FILE* file_calc_suggestions = open_file("calc_suggestions.txt", "a+");

  TablaHash calc_suggestions = get_calc_suggestions(file_calc_suggestions);
  Queue misspelled_words = queue_crear();

  Char_arr buf = char_arr_init(100);
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(fileIn)) != EOF) {
    c = tolower(c); 
    if(('a' <= c) && (c <= 'z')) {
      if(count > char_arr_size(buf) - 2)
        char_arr_resize(buf, char_arr_size(buf)*2);
      char_arr_write(buf, count, c);
      count++;
    } else { 
      aux_spell_check(dic, char_arr_getStr(buf), count, line,
                       calc_suggestions, misspelled_words, 
                       fileOut);
      if(char_arr_size(buf) > 200)
        char_arr_resize(buf, 100);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  aux_spell_check(dic, char_arr_getStr(buf), count, line,
                   calc_suggestions, misspelled_words,
                   fileOut);

  save_suggestions(file_calc_suggestions, calc_suggestions, misspelled_words);

  tablahash_destruir(calc_suggestions);
  queue_destruir(misspelled_words, (FuncionDestructora)str_free);
  char_arr_destroy(buf);
  fclose(file_calc_suggestions);
  fclose(fileOut);
  fclose(fileIn);
}