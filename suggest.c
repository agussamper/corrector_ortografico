#include "suggest.h"
#include "type_operations/strFunc.h"
#include "type_operations/char_str.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void write_suggestion(unsigned *num_suggestions, char* suggestion, FILE *file) {
  if(*num_suggestions == 0)
    fprintf(file, "Quizas quiso decir: %s", suggestion);
  else
    fprintf(file, ", %s", suggestion);
  *num_suggestions += 1;
}

void checkSuggestion(unsigned *suggestions, Queue strObtained, TrieNode dic, 
                 TablaHash mem, Char_str* cstr, FILE *file) {
  if(tablahash_buscar(mem, cstr->str) == NULL) {
    if(checkPresent(dic, cstr->str) == 1) {
      write_suggestion(suggestions, cstr->str, file);
      tablahash_insertar(mem, cstr->str);
    }  
    if(cstr->ch < 3)
      queue_enqueue(strObtained, (FuncionCopia)char_str_cpy, cstr);    
  }
}

void technique1(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Char_str* cstr, FILE *file) {
  char modifiedstr[50];
  strcpy(modifiedstr, cstr->str);
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; modifiedstr[i+1] != '\0'; i++) {        
    if(modifiedstr[i] != modifiedstr[i+1]) {
      char aux = modifiedstr[i];
      modifiedstr[i] = modifiedstr[i+1];
      modifiedstr[i+1] = aux;    
      mcstr.str = modifiedstr;    
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr, file);
      aux = modifiedstr[i];
      modifiedstr[i] = modifiedstr[i+1];
      modifiedstr[i+1] = aux;
    }
  }
}

void technique2(unsigned *suggestions, Queue strObt, TrieNode dic, 
                TablaHash mem, Char_str* cstr, FILE *file) {
  size_t slen = strlen(cstr->str);
  char modifiedstr[slen+2];
  modifiedstr[slen + 1] = '\0';
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(size_t i = 0; i < slen + 1; i++) {    
    for(size_t j = 0; j < slen + 1; j++) {
      if(j < i)
        modifiedstr[j] = cstr->str[j];
      else if(j > i)
        modifiedstr[j] = cstr->str[j-1];      
    }    
    for(int j = 'a'; j <= 'z'; j++) {
      modifiedstr[i] = j;
      mcstr.str = modifiedstr;      
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr, file);
    }
  }
}

void technique3(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Char_str* cstr, FILE *file) {
  if(cstr->str[1] != '\0') {    
    char modifiedstr[50];
    Char_str mcstr;
    mcstr.ch = cstr->ch;
    for(int i = 0; cstr->str[i] != '\0'; i++) {
      if(cstr->str[i] != cstr->str[i+1]) {
        int j = 0;
        for(; cstr->str[j] != '\0'; j++) {
          if(j < i)
            modifiedstr[j] = cstr->str[j];
          else if(j > i)
            modifiedstr[j-1] = cstr->str[j];
        }
        modifiedstr[j-1] = '\0';    
        mcstr.str = modifiedstr;
        checkSuggestion(suggestions, strObt, dic, mem, &mcstr, file);
      }
    }
  }
}

void technique4(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Char_str* cstr, FILE *file) {
  char aux;
  for(int i = 0; cstr->str[i] != '\0'; i++) {
    aux = cstr->str[i];
    for(int j = 'a' ; j <= 'z'; j++) {
      if(aux != j) {
        cstr->str[i] = j;
        checkSuggestion(suggestions, strObt, dic, mem, cstr, file);
      }
    }
    cstr->str[i] = aux;
  }
}

void technique5(unsigned *suggestions, TrieNode dic, TablaHash mem,
                 char* str, FILE *file) {
  for(int i = 0; str[i+1] != '\0'; i++) {
    char str1[50];
    char str2[50];
    char strconcat[100];    

    int m = 0;
    for(m = 0; m < i+1; m++)
      str1[m] = str[m];
    str1[m+1] = '\0';

    int k = i+1; 
    for(; str[k] != '\0'; k++)
      str2[k-(i+1)] = str[k];
    strconcat[k+1] = '\0';
    str2[k-(i+1)] = '\0';

    for(int j = 0; j < k+1; j++) {
      if(j < i+1)
        strconcat[j] = str1[j];
      else if (j == i+1) 
        strconcat[j] = ' ';
      else
        strconcat[j] = str2[j-(i+2)];
    }
    if(tablahash_buscar(mem, strconcat) == NULL) {
      if(checkPresent(dic, str1) == 1) {
        if(checkPresent(dic, str2) == 1) {
          write_suggestion(suggestions, strconcat, file);
          tablahash_insertar(mem, strconcat);
        }
      }
    }
  }
}

void create_suggestions(TrieNode dic, char* str, FILE *file) {
  Queue strsObtained = queue_crear();
  TablaHash mem = tablahash_crear(500, (FuncionCopiadora)str_cpy,
                                  (FuncionComparadora)strcmp,
                                  (FuncionDestructora)str_free,
                                  (FuncionHash)str_KRHash);
  Char_str cstr;
  cstr.str = str;
  cstr.ch = 0;
  queue_enqueue(strsObtained, (FuncionCopia)char_str_cpy, &cstr);
  char strInQueue[50];
  Char_str* front;
  unsigned suggestions = 0;
  while(suggestions < 5 && !queue_vacia(strsObtained)) {
    front = queue_front(strsObtained);
    strcpy(strInQueue, front->str);
    cstr.ch = front->ch + 1;
    cstr.str = strInQueue;
    queue_dequeue(strsObtained, (FuncionDestructora)char_str_free);
    technique1(&suggestions, strsObtained, dic, mem, &cstr, file);
    technique2(&suggestions, strsObtained, dic, mem, &cstr, file);
    technique3(&suggestions, strsObtained, dic, mem, &cstr, file);
    technique4(&suggestions, strsObtained, dic, mem, &cstr, file);
    technique5(&suggestions, dic, mem, strInQueue, file);  
  }
  if(suggestions == 0)
    fputs("No se encontraron sugerencias", file);
  fputs("\n\n", file);
  queue_destruir(strsObtained, (FuncionDestructora)char_str_free);
  tablahash_destruir(mem);
}
