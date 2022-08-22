#include "spell_checker.h"
#include "type_operations/int_str.h"
#include "type_operations/strFunc.h"
#include "IO.h"
#include "suggest.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void addToStack(Pila pila, TablaHash dic, char* buf,
                unsigned count, unsigned line,
                unsigned max) {
  if(count > 0) {
    Int_str* istr = NULL;
    if(count < max) {
      buf[count] = '\0';
      if(tablahash_buscar(dic, buf) == NULL) {
        istr = malloc(sizeof(Int_str)); 
        istr->str = malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(istr->str, buf);
        istr->num = line;      
        pila_apilar(pila, istr, (FuncionCopia)int_str_return);
      }
    } else {
      buf[max] = '\0';
      istr = malloc(sizeof(Int_str));
      istr->str = malloc(sizeof(char) * (max + 1));
      strcpy(istr->str, buf);
      for(int i = max-1; (max - 4) < i; i--)
        istr->str[i] = '.';
      istr->num = line;
      pila_apilar(pila, istr, (FuncionCopia)int_str_return);
    }    
  }
}

Pila spell_check(TablaHash dic, const char* path) {
  FILE* file = open_file(path, "r");
  Pila pila = pila_crear();

  unsigned max = 30;
  char buf[max];
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(file)) != EOF) {
    c = tolower(c); 
    if(97 <= c && c <= 122) {
      buf[count] = c;
      count++;
    } else {
      addToStack(pila, dic, buf, count, line, max);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  addToStack(pila, dic, buf, count, line, max);
  fclose(file);
  return pila;
}

void print_suggestions(TablaHash dictionary, const char* path) {
  Pila missp_words = spell_check(dictionary, path);
  Pila suggestions = NULL; 
  Int_str* istr;
  while(!pila_es_vacia(missp_words)) {
    istr = pila_tope(missp_words);
    printf("Linea %d, '%s' no esta en el diccionario.\n", istr->num, istr->str);
    suggestions = create_suggestions(dictionary, istr->str);
    if(pila_es_vacia(suggestions)) {
      printf("No se encontraron sugerencias.\n");
      //pila_destruir(suggestions, (FuncionDestructora)str_free);
    } else {
      printf("Quizas quiso decir: ");
      while(!pila_es_vacia(suggestions)) {
        if(pila_size(suggestions) == 1)
          printf("%s\n", pila_tope(suggestions));
        else
          printf("%s, ", pila_tope(suggestions));
        pila_desapilar(suggestions, (FuncionDestructora)str_free);
      }
    }
    pila_desapilar(missp_words, (FuncionDestructora)int_str_free);        
    pila_destruir(suggestions, (FuncionDestructora)str_free);
  }
  pila_destruir(missp_words, (FuncionDestructora)int_str_free); 
}