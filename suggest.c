#include "suggest.h"
#include "type_operations/strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void write_suggestion(unsigned num_suggestions, char *suggestion, FILE *f_out) {
  if(num_suggestions == 0)
    fprintf(f_out, "Quizas quiso decir: %s", suggestion);
  else
    fprintf(f_out, ", %s", suggestion);  
}

void save_suggestion(char** suggestions, unsigned num_suggestion,
                      Str_len_int* str_len_dist) {
  suggestions[num_suggestion] = malloc(sizeof(char) * (str_len_dist->len_str +1));
  strcpy(suggestions[num_suggestion], str_len_dist->str);
}

int search_suggestion(char** suggestions, unsigned num_suggestion,
                        char* suggestion) {                          
  for(unsigned i = 0; i < num_suggestion; i++) {
    if(strcmp(suggestions[i], suggestion) == 0)
      return 1; 
  }
  return 0;
}

void checkSuggestion(unsigned *num_suggestions, Queue strObtained, TrieNode dic, 
                 char** suggestions, Str_len_int* str_len_dist, FILE* f_out) {
  if(search_suggestion(suggestions, *num_suggestions, str_len_dist->str) == 0) {
    if(trie_checkPresent(dic, str_len_dist->str) == 1) {
      write_suggestion(*num_suggestions, str_len_dist->str, f_out);
      save_suggestion(suggestions, *num_suggestions, str_len_dist);      
      *num_suggestions += 1;
    }  
    if(str_len_dist->num < 3)
      queue_enqueue(strObtained, (FuncionCopia)str_len_int_cpy, str_len_dist);    
  }
}

void technique1(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Str_len_int* str_len_dist, FILE* f_out) {  
  char* str = str_len_dist->str;
  for(int i = 0; str[i+1] != '\0' && *num_suggestions < 5; i++) {        
    if(str[i] != str[i+1]) {
      char aux = str[i];
      str[i] = str[i+1];
      str[i+1] = aux;        
      checkSuggestion(num_suggestions, strObt, dic,
                       suggestions, str_len_dist, f_out);
      aux = str[i];
      str[i] = str[i+1];
      str[i+1] = aux;
    }
  }
}

void technique2(unsigned *num_suggestions, Queue strObt, TrieNode dic, 
                char** suggestions, Str_len_int* str_len_dist, FILE* f_out) {
  char* str = str_len_dist->str;
  unsigned str_len = str_len_dist->len_str;
  char modifiedstr[str_len+2];
  modifiedstr[str_len + 1] = '\0';
  Str_len_int mstr_len_dist;
  mstr_len_dist.len_str = str_len_dist->len_str + 1;
  mstr_len_dist.num = str_len_dist->num;
  for(unsigned i = 0; i < str_len + 1 && *num_suggestions < 5; i++) {    
    for(unsigned j = 0; j < str_len + 1; j++) {
      if(j < i)
        modifiedstr[j] = str[j];
      else if(j > i)
        modifiedstr[j] = str[j-1];      
    }    
    for(int j = 'a'; j <= 'z' && *num_suggestions < 5; j++) {
      modifiedstr[i] = j;
      mstr_len_dist.str = modifiedstr;      
      checkSuggestion(num_suggestions, strObt, dic, suggestions, &mstr_len_dist, f_out);
    }
  }
}

void technique3(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Str_len_int* str_len_dist, FILE* f_out) {
  char* str = str_len_dist->str;
  if(str[1] != '\0') {
    unsigned str_len = str_len_dist->len_str;    
    char modifiedstr[str_len];
    Str_len_int mstr_len_dist;
    mstr_len_dist.len_str = str_len-1;
    mstr_len_dist.num = str_len_dist->num;
    for(int i = 0; str[i] != '\0' && *num_suggestions < 5; i++) {
      if(str[i] != str[i+1]) {
        int j = 0;
        for(; str[j] != '\0'; j++) {
          if(j < i)
            modifiedstr[j] = str[j];
          else if(j > i)
            modifiedstr[j-1] = str[j];
        }
        modifiedstr[j-1] = '\0';    
        mstr_len_dist.str = modifiedstr;
        checkSuggestion(num_suggestions, strObt, dic, suggestions, &mstr_len_dist, f_out);
      }
    }
  }
}

void technique4(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Str_len_int* str_len_dist, FILE* f_out) {
  char aux;
  char* str = str_len_dist->str;
  for(int i = 0; str[i] != '\0' && *num_suggestions < 5; i++) {
    aux = str[i];
    for(int j = 'a' ; j <= 'z' && *num_suggestions < 5; j++) {
      if(aux != j) {
        str[i] = j;
        checkSuggestion(num_suggestions, strObt, dic, suggestions, str_len_dist, f_out);
      }
    }
    str[i] = aux;
  }
}

void technique5(unsigned *num_suggestions, TrieNode dic, char** suggestions,
                 Str_len_int* str_len_dist, FILE* f_out) {
  char* str = str_len_dist->str;
  unsigned str_len = str_len_dist->len_str;
  for(unsigned i = 0; str[i+1] != '\0' && *num_suggestions < 5; i++) {
    char str1[str_len];
    char str2[str_len];
    char strconcat[str_len+2];
    strconcat[str_len+2] = '\0';    

    for(unsigned m = 0; m < i+1; m++)
      str1[m] = str[m];
    str1[i+1] = '\0';

    unsigned k = i+1;
    for(; str[k] != '\0'; k++)
      str2[k-(i+1)] = str[k];    
    str2[k-(i+1)] = '\0';

    for(unsigned j = 0; j < str_len+2; j++) {
      if(j < i+1)
        strconcat[j] = str1[j];
      else if (j == i+1) 
        strconcat[j] = ' ';
      else
        strconcat[j] = str2[j-(i+2)];
    }
    if(search_suggestion(suggestions, *num_suggestions, strconcat) == 0) {
      if(trie_checkPresent(dic, str1) == 1) {
        if(trie_checkPresent(dic, str2) == 1) {
          write_suggestion(*num_suggestions, strconcat, f_out);

          Str_len_int new_suggestion;
          new_suggestion.str = strconcat;
          new_suggestion.len_str = str_len+1;
          save_suggestion(suggestions, *num_suggestions, &new_suggestion);
          *num_suggestions += 1;
        }
      }
    }
  }
}

char** create_suggestions(TrieNode dic, char* str, FILE *f_out) {
  Queue strsObtained = queue_crear();  
  Str_len_int str_len_dist;
  
  str_len_dist.str = str;
  str_len_dist.len_str = strlen(str);
  str_len_dist.num = 0;
  queue_enqueue(strsObtained, (FuncionCopia)str_len_int_cpy, &str_len_dist);  
  Str_len_int* front;
  char** suggestions = malloc(sizeof(char*) * 5);
  for(int i = 0; i < 5; i++)
    suggestions[i] = NULL;
  unsigned num_suggestions = 0;
  while(num_suggestions < 5 && !queue_vacia(strsObtained)) {
    front = queue_front(strsObtained);    
    char strInQueue[front->len_str];
    strcpy(strInQueue, front->str);
    str_len_dist.num = front->num + 1;
    str_len_dist.str = strInQueue;
    str_len_dist.len_str = front->len_str;
    queue_dequeue(strsObtained, (FuncionDestructora)str_len_int_free);    
    technique1(&num_suggestions, strsObtained, dic, suggestions, &str_len_dist, f_out);
    technique2(&num_suggestions, strsObtained, dic, suggestions, &str_len_dist, f_out);
    technique3(&num_suggestions, strsObtained, dic, suggestions, &str_len_dist, f_out);
    technique4(&num_suggestions, strsObtained, dic, suggestions, &str_len_dist, f_out);
    technique5(&num_suggestions, dic, suggestions, &str_len_dist, f_out);  
  }
  if(num_suggestions == 0) {
    fputs("No se encontraron sugerencias", f_out);
    free(suggestions);
    suggestions = NULL;
  }
  fputs("\n\n", f_out);
  queue_destruir(strsObtained, (FuncionDestructora)str_len_int_free);
  return suggestions;
}
