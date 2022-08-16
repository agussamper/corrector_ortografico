#include "suggest.h"
#include "type_operations/strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void technique1(Pila inDic, Pila strObt, TablaHash dic, char* str) {
  size_t slen = strlen(str);  
  char mstr[slen+1];
  strcpy(mstr, str);
  for(int i = 0; i < slen-1; i++) {        
    char aux = mstr[i];
    mstr[i] = mstr[i+1];
    mstr[i+1] = aux;
    if(tablahash_buscar(dic, mstr) != NULL)
      pila_apilar(inDic, mstr, (FuncionCopia)str_cpy);
    pila_apilar(strObt, mstr, (FuncionCopia)str_cpy);
    aux = mstr[i];
    mstr[i] = mstr[i+1];
    mstr[i+1] = aux;
  }
}

void technique2(Pila inDic, Pila strObt, TablaHash dic, char* str) {
  size_t slen = strlen(str);
  char mstr[slen+1];
  mstr[slen+1] = '\0';
  for(int i = 0; i < slen + 1; i++) {        
    for(int j = 0; j < slen + 1; j++) {
      if(j < i)
        mstr[j] = str[j];
      else if(j > i)
        mstr[j] = str[j-1];
    }
    for(int j = 97; j < 123; j++) {
      mstr[i] = j;      
      if(tablahash_buscar(dic, mstr) != NULL)
        pila_apilar(inDic, mstr, (FuncionCopia)str_cpy);
      pila_apilar(strObt, mstr, (FuncionCopia)str_cpy);
    }    
  }
}

void technique3(Pila inDic, Pila strObt, TablaHash dic, char* str) {
  size_t slen = strlen(str);
  char mstr[slen-1];
  mstr[slen-1] = '\0';
  for(int i = 0; i < slen; i++) {
    for(int j = 0; j < slen; j++) {
      if(j < i)
        mstr[j] = str[j];
      else if(j > i)
        mstr[j-1] = str[j];
    }    
    if(tablahash_buscar(dic, mstr) != NULL)
      pila_apilar(inDic, mstr, (FuncionCopia)str_cpy);
    pila_apilar(strObt, mstr, (FuncionCopia)str_cpy);
  }
}

void technique4(Pila inDic, Pila strObt, TablaHash dic, char* str) {
  size_t slen = strlen(str);
  char mstr[slen];
  strcpy(mstr, str);
  char aux;
  for(int i = 0; i < slen; i++) {
    aux = mstr[i];
    for(int j = 97 ; j < 123; j++) {
      if(aux != j) {
        mstr[i] = j;
        if(tablahash_buscar(dic, mstr) != NULL)
          pila_apilar(inDic, mstr, (FuncionCopia)str_cpy);
        pila_apilar(strObt, mstr, (FuncionCopia)str_cpy);
      }
    }
    mstr[i] = aux;
  }
}

//TODO: Intentar optimizar
void technique5(Pila inDic, TablaHash dic, char* str) {
  size_t slen = strlen(str);
  for(int i = 0; i < slen; i++) {
    char str1[i+1];
    char str2[slen-(i+1)];    
    strncpy(str1, str, i+1);
    str1[i+1] = '\0';
    strncpy(str2, &str[i+1], slen-(i+1));
    str2[slen-(i+1)] = '\0';
    if(tablahash_buscar(dic, str1) != NULL && tablahash_buscar(dic, str2) != NULL) {      
      char toAdd[slen+1];
      strcpy(toAdd, str1);
      toAdd[i+1] = ' ';
      toAdd[i+2] = '\0';
      strcat(toAdd, str2);
      pila_apilar(inDic, toAdd, (FuncionCopia)str_cpy);
    }
  }
}