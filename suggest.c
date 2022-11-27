#include "suggest.h"
#include "type_operations/strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void write_suggestion(unsigned *num_suggestions, char *suggestion, FILE *f_out) {
  if(*num_suggestions == 0)
    fprintf(f_out, "Quizas quiso decir: %s", suggestion);
  else
    fprintf(f_out, ", %s", suggestion);  
}

void save_suggestion(char** suggestions, unsigned *num_suggestion,
                      char* suggestion) { //TODO: cambiar para que reciba istr en cambio de suggestion
  suggestions[*num_suggestion] = malloc(sizeof(char) * (strlen(suggestion)+1));
  strcpy(suggestions[*num_suggestion], suggestion);
}

// Busca en suggestions la sugerencia pasada por parametros, si la
// encuentra devuelve 1, en caso contrario 0
int serach_suggestion(char** suggestions, unsigned *num_suggestion,
                        char* suggestion) {
  unsigned num_sugg = *num_suggestion;
  for(unsigned i = 0; i < num_sugg; i++) {
    if(strcmp(suggestions[i], suggestion) == 0)
      return 1; 
  }
  return 0;
}

void checkSuggestion(unsigned *num_suggestions, Queue strObtained, TrieNode dic, 
                 char** suggestions, Int_str* istr, FILE* f_out) {
  if(serach_suggestion(suggestions, num_suggestions, istr->str) == 0) {
    if(trie_checkPresent(dic, istr->str) == 1) {
      write_suggestion(num_suggestions, istr->str, f_out);
      save_suggestion(suggestions, num_suggestions, istr->str);      
      *num_suggestions += 1;
    }  
    if(istr->num < 3)
      queue_enqueue(strObtained, (FuncionCopia)int_str_cpy, istr);    
  }
}

void technique1(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Int_str* istr, FILE* f_out) {  
  for(int i = 0; istr->str[i+1] != '\0' && *num_suggestions < 5; i++) {        
    if(istr->str[i] != istr->str[i+1]) {
      char aux = istr->str[i];
      istr->str[i] = istr->str[i+1];
      istr->str[i+1] = aux;        
      checkSuggestion(num_suggestions, strObt, dic, suggestions, istr, f_out);
      aux = istr->str[i];
      istr->str[i] = istr->str[i+1];
      istr->str[i+1] = aux;
    }
  }
}

void technique2(unsigned *num_suggestions, Queue strObt, TrieNode dic, 
                char** suggestions, Int_str* istr, size_t str_len, FILE* f_out) {
  char modifiedstr[str_len+2];
  modifiedstr[str_len + 1] = '\0';
  Int_str mistr;
  mistr.num = istr->num;
  for(size_t i = 0; i < str_len + 1 && *num_suggestions < 5; i++) {    
    for(size_t j = 0; j < str_len + 1; j++) {
      if(j < i)
        modifiedstr[j] = istr->str[j];
      else if(j > i)
        modifiedstr[j] = istr->str[j-1];      
    }    
    for(int j = 'a'; j <= 'z' && *num_suggestions < 5; j++) {
      modifiedstr[i] = j;
      mistr.str = modifiedstr;      
      checkSuggestion(num_suggestions, strObt, dic, suggestions, &mistr, f_out);
    }
  }
}

void technique3(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Int_str* istr, size_t str_len, FILE* f_out) {
  if(istr->str[1] != '\0') {    
    char modifiedstr[str_len];
    Int_str mistr;
    mistr.num = istr->num;
    for(int i = 0; istr->str[i] != '\0' && *num_suggestions < 5; i++) {
      if(istr->str[i] != istr->str[i+1]) {
        int j = 0;
        for(; istr->str[j] != '\0'; j++) {
          if(j < i)
            modifiedstr[j] = istr->str[j];
          else if(j > i)
            modifiedstr[j-1] = istr->str[j];
        }
        modifiedstr[j-1] = '\0';    
        mistr.str = modifiedstr;
        checkSuggestion(num_suggestions, strObt, dic, suggestions, &mistr, f_out);
      }
    }
  }
}

void technique4(unsigned *num_suggestions, Queue strObt, TrieNode dic,
                char** suggestions, Int_str* istr, FILE* f_out) {
  char aux;
  for(int i = 0; istr->str[i] != '\0' && *num_suggestions < 5; i++) {
    aux = istr->str[i];
    for(int j = 'a' ; j <= 'z' && *num_suggestions < 5; j++) {
      if(aux != j) {
        istr->str[i] = j;
        checkSuggestion(num_suggestions, strObt, dic, suggestions, istr, f_out);
      }
    }
    istr->str[i] = aux;
  }
}

void technique5(unsigned *num_suggestions, TrieNode dic, char** suggestions,
                 char* str, size_t str_len, FILE* f_out) {
  for(size_t i = 0; str[i+1] != '\0' && *num_suggestions < 5; i++) {
    char str1[str_len];
    char str2[str_len];
    char strconcat[str_len+2];
    strconcat[str_len+2] = '\0';    

    for(size_t m = 0; m < i+1; m++)
      str1[m] = str[m];
    str1[i+1] = '\0';

    size_t k = i+1;
    for(; str[k] != '\0'; k++)
      str2[k-(i+1)] = str[k];    
    str2[k-(i+1)] = '\0';

    for(size_t j = 0; j < str_len+2; j++) {
      if(j < i+1)
        strconcat[j] = str1[j];
      else if (j == i+1) 
        strconcat[j] = ' ';
      else
        strconcat[j] = str2[j-(i+2)];
    }
    if(serach_suggestion(suggestions, num_suggestions, strconcat) == 0) {
      if(trie_checkPresent(dic, str1) == 1) {
        if(trie_checkPresent(dic, str2) == 1) {
          write_suggestion(num_suggestions, strconcat, f_out);
          save_suggestion(suggestions, num_suggestions, strconcat);
          *num_suggestions += 1;
        }
      }
    }
  }
}

char** create_suggestions(TrieNode dic, char* str, FILE *f_out) {
  Queue strsObtained = queue_crear();  
  Int_str istr;
  istr.str = str;
  istr.num = 0;
  queue_enqueue(strsObtained, (FuncionCopia)int_str_cpy, &istr);  
  Int_str* front;
  char** suggestions = malloc(sizeof(char*) * 5);
  for(int i = 0; i < 5; i++)
    suggestions[i] = NULL;
  unsigned num_suggestions = 0;
  while(num_suggestions < 5 && !queue_vacia(strsObtained)) {
    front = queue_front(strsObtained);
    size_t str_len = strlen(front->str); //TODO: guardar strlen directamente en istr
    char strInQueue[str_len];
    strcpy(strInQueue, front->str);
    istr.num = front->num + 1;
    istr.str = strInQueue;
    queue_dequeue(strsObtained, (FuncionDestructora)int_str_free);    
    technique1(&num_suggestions, strsObtained, dic, suggestions, &istr, f_out);
    technique2(&num_suggestions, strsObtained, dic, suggestions, &istr, str_len, f_out);
    technique3(&num_suggestions, strsObtained, dic, suggestions, &istr, str_len, f_out);
    technique4(&num_suggestions, strsObtained, dic, suggestions, &istr, f_out);
    technique5(&num_suggestions, dic, suggestions, strInQueue, str_len, f_out);  
  }
  if(num_suggestions == 0) {
    fputs("No se encontraron sugerencias", f_out);
    free(suggestions);
    suggestions = NULL;
  }
  fputs("\n\n", f_out);
  queue_destruir(strsObtained, (FuncionDestructora)int_str_free);
  return suggestions;
}
