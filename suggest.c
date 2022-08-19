#include "suggest.h"
#include "type_operations/strFunc.h"
#include "type_operations/char_str.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void addToStacks(Pila inDic, Pila strObt, TablaHash dic, 
                 TablaHash mem, Char_str* cstr) {
  if(tablahash_buscar(mem, cstr->str) == NULL) {
    if(tablahash_buscar(dic, cstr->str) != NULL)
      pila_apilar(inDic, cstr->str, (FuncionCopia)str_cpy);
    if(cstr->ch < 3)
      pila_apilar(strObt, cstr, (FuncionCopia)char_str_cpy);
    tablahash_insertar(mem, cstr->str);
  }
}

void technique1(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str);  
  char mstr[slen+1];
  strcpy(mstr, cstr->str);
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; i < slen-1; i++) {        
    char aux = mstr[i];
    mstr[i] = mstr[i+1];
    mstr[i+1] = aux;    
    mcstr.str = mstr;    
    addToStacks(inDic, strObt, dic, mem, &mcstr);
    aux = mstr[i];
    mstr[i] = mstr[i+1];
    mstr[i+1] = aux;
  }
}

void technique2(Pila inDic, Pila strObt, TablaHash dic, 
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
    for(int j = 97; j < 123; j++) {
      mstr[i] = j;
      mcstr.str = mstr;      
      addToStacks(inDic, strObt, dic, mem, &mcstr);
    }    
  }
}

void technique3(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str);
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
    addToStacks(inDic, strObt, dic, mem, &mcstr);
  }
}

void technique4(Pila inDic, Pila strObt, TablaHash dic,
                TablaHash mem, Char_str* cstr) {
  size_t slen = strlen(cstr->str);
  char mstr[slen+1];
  strcpy(mstr, cstr->str);
  char aux;
  Char_str mcstr;
  mcstr.ch = cstr->ch;
  for(int i = 0; i < slen; i++) {
    aux = mstr[i];
    for(int j = 97 ; j < 123; j++) {
      if(aux != j) {
        mstr[i] = j;
        mcstr.str = mstr;
        addToStacks(inDic, strObt, dic, mem, &mcstr);
      }
    }
    mstr[i] = aux;
  }
}

void technique5(Pila inDic, TablaHash dic, TablaHash mem, char* str) {
  size_t slen = strlen(str);
  for(int i = 0; i < slen; i++) {
    char str1[i+2];
    char str2[slen-i];    
    strncpy(str1, str, i+1);
    str1[i+1] = '\0';
    strncpy(str2, &str[i+1], slen-(i+1));
    str2[slen-(i+1)] = '\0';
    char strconc[slen+2];
    for(int j = 0; j < slen+1; j++) {
      if(j < i+1)
        strconc[j] = str1[j];
      else if (j == i+1) 
        strconc[j] = ' ';
      else
        strconc[j] = str2[j-(i+2)];
    }
    strconc[slen+1] = '\0';
    if(tablahash_buscar(mem, strconc) == NULL) {
      if(tablahash_buscar(dic, str1) != NULL &&
         tablahash_buscar(dic, str2) != NULL)    
        pila_apilar(inDic, strconc, (FuncionCopia)str_cpy);
    }
  }
}

Pila create_suggestions(TablaHash dic, char* str) {
  if(strlen(str) > 50)
    return NULL;
  Pila inDic = pila_crear();
  Pila strObt = pila_crear();
  TablaHash mem = tablahash_crear(100, (FuncionCopiadora)str_cpy,
                                  (FuncionComparadora)strcmp,
                                  (FuncionDestructora)str_free,
                                  (FuncionHash)str_KRHash);
  Char_str cstr;
  cstr.str = str;
  cstr.ch = 0;
  pila_apilar(strObt, &cstr, (FuncionCopia)char_str_cpy);
  char strInS[50];
  int m = 0;
  Char_str* top;
  while(pila_size(inDic) <= 5 && !pila_es_vacia(strObt)) {
    top = pila_tope(strObt);
    strcpy(strInS, top->str);
    cstr.ch = top->ch + 1;
    cstr.str = strInS;
    pila_desapilar(strObt, (FuncionDestructora)char_str_free);      
    technique1(inDic, strObt, dic, mem, &cstr);
    technique2(inDic, strObt, dic, mem, &cstr);
    technique3(inDic, strObt, dic, mem, &cstr);
    technique4(inDic, strObt, dic, mem, &cstr);
    technique5(inDic, dic, mem, strInS);
  }
  pila_destruir(strObt, (FuncionDestructora)char_str_free);
  tablahash_destruir(mem);
  return inDic;
}