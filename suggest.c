#include "suggest.h"
#include "type_operations/strFunc.h"
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
                 TablaHash mem, Int_str* istr, FILE *file) {
  if(tablahash_buscar(mem, istr->str) == NULL) {
    if(trie_checkPresent(dic, istr->str) == 1) {
      write_suggestion(suggestions, istr->str, file);
      tablahash_insertar(mem, istr->str);
    }  
    if(istr->num < 3)
      queue_enqueue(strObtained, (FuncionCopia)int_str_cpy, istr);    
  }
}

void technique1(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Int_str* istr, FILE *file) {  
  for(int i = 0; istr->str[i+1] != '\0'; i++) {        
    if(istr->str[i] != istr->str[i+1]) {
      char aux = istr->str[i];
      istr->str[i] = istr->str[i+1];
      istr->str[i+1] = aux;        
      checkSuggestion(suggestions, strObt, dic, mem, istr, file);
      aux = istr->str[i];
      istr->str[i] = istr->str[i+1];
      istr->str[i+1] = aux;
    }
  }
}

void technique2(unsigned *suggestions, Queue strObt, TrieNode dic, 
                TablaHash mem, Int_str* istr, size_t str_len, FILE *file) {
  char modifiedstr[str_len+2];
  modifiedstr[str_len + 1] = '\0';
  Int_str mistr;
  mistr.num = istr->num;
  for(size_t i = 0; i < str_len + 1; i++) {    
    for(size_t j = 0; j < str_len + 1; j++) {
      if(j < i)
        modifiedstr[j] = istr->str[j];
      else if(j > i)
        modifiedstr[j] = istr->str[j-1];      
    }    
    for(int j = 'a'; j <= 'z'; j++) {
      modifiedstr[i] = j;
      mistr.str = modifiedstr;      
      checkSuggestion(suggestions, strObt, dic, mem, &mistr, file);
    }
  }
}

void technique3(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Int_str* istr, size_t str_len, FILE *file) {
  if(istr->str[1] != '\0') {    
    char modifiedstr[str_len];
    Int_str mistr;
    mistr.num = istr->num;
    for(int i = 0; istr->str[i] != '\0'; i++) {
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
        checkSuggestion(suggestions, strObt, dic, mem, &mistr, file);
      }
    }
  }
}

void technique4(unsigned *suggestions, Queue strObt, TrieNode dic,
                TablaHash mem, Int_str* istr, FILE *file) {
  char aux;
  for(int i = 0; istr->str[i] != '\0'; i++) {
    aux = istr->str[i];
    for(int j = 'a' ; j <= 'z'; j++) {
      if(aux != j) {
        istr->str[i] = j;
        checkSuggestion(suggestions, strObt, dic, mem, istr, file);
      }
    }
    istr->str[i] = aux;
  }
}

void technique5(unsigned *suggestions, TrieNode dic, TablaHash mem,
                 char* str, size_t str_len, FILE *file) {
  for(size_t i = 0; str[i+1] != '\0'; i++) {
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
    if(tablahash_buscar(mem, strconcat) == NULL) {
      if(trie_checkPresent(dic, str1) == 1) {
        if(trie_checkPresent(dic, str2) == 1) {
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

  Int_str istr;
  istr.str = str;
  istr.num = 0;
  queue_enqueue(strsObtained, (FuncionCopia)int_str_cpy, &istr);  
  Int_str* front;
  unsigned suggestions = 0;
  while(suggestions < 5 && !queue_vacia(strsObtained)) {
    front = queue_front(strsObtained);
    size_t str_len = strlen(front->str);
    char strInQueue[str_len];
    strcpy(strInQueue, front->str);
    istr.num = front->num + 1;
    istr.str = strInQueue;
    queue_dequeue(strsObtained, (FuncionDestructora)int_str_free);
    technique1(&suggestions, strsObtained, dic, mem, &istr, file);
    technique2(&suggestions, strsObtained, dic, mem, &istr, str_len, file);
    technique3(&suggestions, strsObtained, dic, mem, &istr, str_len, file);
    technique4(&suggestions, strsObtained, dic, mem, &istr, file);
    technique5(&suggestions, dic, mem, strInQueue, str_len, file);  
  }
  if(suggestions == 0)
    fputs("No se encontraron sugerencias", file);
  fputs("\n\n", file);
  queue_destruir(strsObtained, (FuncionDestructora)int_str_free);
  tablahash_destruir(mem);
}
