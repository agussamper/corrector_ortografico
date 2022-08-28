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
  size_t slen = strlen(cstr->str);  
  char mstr[slen+1];
  strcpy(mstr, cstr->str);
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; i < slen-1; i++) {        
    if(mstr[i] != mstr[i+1]) {
      char aux = mstr[i];
      mstr[i] = mstr[i+1];
      mstr[i+1] = aux;    
      mcstr.str = mstr;    
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
      aux = mstr[i];
      mstr[i] = mstr[i+1];
      mstr[i+1] = aux;
    }
  }
}

void technique2(unsigned *suggestions, Queue strObt, TablaHash dic, 
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str);
  char mstr[slen+2];
  mstr[slen+1] = '\0';
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; i < slen + 1; i++) {        
    for(int j = 0; j < slen + 1; j++) {
      if(j < i)
        mstr[j] = cstr->str[j];
      else if(j > i)
        mstr[j] = cstr->str[j-1];
    }
    for(int j = 'a'; j < 'z'; j++) {
      mstr[i] = j;
      mcstr.str = mstr;      
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
    }    
  }
}

void technique3(unsigned *suggestions, Queue strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str); //TODO: funcion con caso especial si todos los caracteres son iguales para no correr todo el resto
  if(slen > 1) {    
    char mstr[slen];
    mstr[slen-1] = '\0';
    Char_str mcstr;
    mcstr.ch = cstr->ch;
    for(int i = 0; i < slen; i++) {
      for(int j = 0; j < slen; j++) {
        if(j < i)
          mstr[j] = cstr->str[j];
        else if(j > i)
          mstr[j-1] = cstr->str[j];
      }    
      mcstr.str = mstr;
      checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
    }
  }
}

void technique4(unsigned *suggestions, Queue strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str);
  char mstr[slen+1];
  strcpy(mstr, cstr->str);
  char aux;
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; i < slen; i++) {
    aux = mstr[i];
    for(int j = 'a' ; j < 'z'; j++) {
      if(aux != j) {
        mstr[i] = j;
        mcstr.str = mstr;
        checkSuggestion(suggestions, strObt, dic, mem, &mcstr);
      }
    }
    mstr[i] = aux;
  }
}

void technique5(unsigned *suggestions, TablaHash dic, TablaHash mem, char* str) {
  size_t slen = strlen(str);
  for(int i = 0; i < slen; i++) {
    char str1[i+2];
    char str2[slen-i];    
    strncpy(str1, str, i+1);
    str1[i+1] = '\0';
    strncpy(str2, &str[i+1], slen-(i+1));
    str2[slen-(i+1)] = '\0';
    char strconcat[slen+2];
    for(int j = 0; j < slen+1; j++) {
      if(j < i+1)
        strconcat[j] = str1[j];
      else if (j == i+1) 
        strconcat[j] = ' ';
      else
        strconcat[j] = str2[j-(i+2)];
    }
    strconcat[slen+1] = '\0';
    if(tablahash_buscar(mem, strconcat) == NULL) {
      if(tablahash_buscar(dic, str1) != NULL &&
         tablahash_buscar(dic, str2) != NULL) {
         print_suggestion(suggestions, strconcat);
         tablahash_insertar(mem, strconcat);
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
