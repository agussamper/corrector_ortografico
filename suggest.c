#include "suggest.h"
#include "type_operations/strFunc.h"
#include "type_operations/char_str.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//TODO: Guardar las sugerencias encontradas para una palabra para
// reusarlas si ya fueron buscadas anteriormente

void print_suggestion(unsigned *num_suggestions, char* suggestion) {
  if(*num_suggestions == 0)
    printf("Quizas quiso decir: %s", suggestion);
  else
    printf(", %s", suggestion);
  *num_suggestions += 1;
}

void checkSuggestion(unsigned *suggestions, Queue strObtained, TablaHash dic, 
                 TablaHash mem, Char_str* cstr) {
  if(tablahash_buscar(mem, cstr->str) == NULL) {
    if(tablahash_buscar(dic, cstr->str) != NULL) {
      print_suggestion(suggestions, cstr->str);
      tablahash_insertar(mem, cstr->str);
    }  
    if(cstr->ch < 3)
      queue_enqueue(strObtained, (FuncionCopia)char_str_cpy, cstr);    
  }
}

void technique1(unsigned *suggestions, Queue strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
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
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
      aux = modifiedstr[i];
      modifiedstr[i] = modifiedstr[i+1];
      modifiedstr[i+1] = aux;
    }
  }
}

void technique2(unsigned *suggestions, Queue strObt, TablaHash dic, 
                TablaHash mem, Char_str* cstr) {
  char modifiedstr[50];
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  char flag = 0;
  int k1 = 100;
  for(int i = 0; i < k1; i++) {
    char flag2 = 0;
    int k2 = 100;
    int j = 0;    
    for(; j < k2; j++) {
      if(j < i)
        modifiedstr[j] = cstr->str[j];
      else if(j > i)
        modifiedstr[j] = cstr->str[j-1];
      if(flag2 == 0 && cstr->str[j] == '\0') {
        k2 = j + 1;
        flag2 = 1;
      }
    }
    modifiedstr[j] = '\0';
    for(int j = 'a'; j <= 'z'; j++) {
      if(j != cstr->str[i]) {
        modifiedstr[i] = j;
        mcstr.str = modifiedstr;      
        checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
      }
    }
    if(flag == 0 && cstr->str[i] == '\0') {
      k1 = i + 1;    
      flag = 1;
    }
  }
}

void technique3(unsigned *suggestions, Queue strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
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
        checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
      }
    }
  }
}

void technique4(unsigned *suggestions, Queue strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  char aux;
  for(int i = 0; cstr->str[i] != '\0'; i++) {
    aux = cstr->str[i];
    for(int j = 'a' ; j <= 'z'; j++) {
      if(aux != j) {
        cstr->str[i] = j;
        checkSuggestion(suggestions, strObt, dic, mem, cstr);
      }
    }
    cstr->str[i] = aux;
  }
}

void technique5(unsigned *suggestions, TablaHash dic, TablaHash mem, char* str) {
  for(int i = 0; str[i+1] != '\0'; i++) {
    char str1[50];
    char str2[50];
    char strconcat[100];    

    int m = 0;
    for(int m = 0; m < i+1; m++)
      str1[m] = str[m];
    str1[m] = '\0';

    int k = i+1; 
    for(; str[k] != '\0'; k++)
      str2[k-(i+1)] = str[k];
    strconcat[k+1] = '\0';
    str2[k] = '\0';

    for(int j = 0; j < k+1; j++) {
      if(j < i+1)
        strconcat[j] = str1[j];
      else if (j == i+1) 
        strconcat[j] = ' ';
      else
        strconcat[j] = str2[j-(i+2)];
    }
    if(tablahash_buscar(mem, strconcat) == NULL) {
      if(tablahash_buscar(dic, str1) != NULL) {
        if(tablahash_buscar(dic, str2) != NULL) {
          print_suggestion(suggestions, strconcat);
          tablahash_insertar(mem, strconcat);
        }
      }
    }
  }
}

void create_suggestions(TablaHash dic, char* str) {
  Queue strsObtained = queue_crear();
  TablaHash mem = tablahash_crear(1000, (FuncionCopiadora)str_cpy,
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
    technique1(&suggestions, strsObtained, dic, mem, &cstr);
    technique2(&suggestions, strsObtained, dic, mem, &cstr);
    technique3(&suggestions, strsObtained, dic, mem, &cstr);
    technique4(&suggestions, strsObtained, dic, mem, &cstr);
    technique5(&suggestions, dic, mem, strInQueue);  
  }
  if(suggestions == 0)
    printf("No se encontraron sugerencias");
  puts("");
  queue_destruir(strsObtained, (FuncionDestructora)char_str_free);
  tablahash_destruir(mem);
}
