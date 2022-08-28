#include "spell_checker.h"
#include "type_operations/int_str.h"
#include "type_operations/strFunc.h"
#include "IO.h"
#include "suggest.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//TODO: comentar
void addToQueue(Queue queue, TablaHash dic, char* buf,
                unsigned count, unsigned line) {
  if(count > 0) {
    Int_str* istr = NULL;
    buf[count] = '\0';
    if(tablahash_buscar(dic, buf) == NULL) {
      istr = malloc(sizeof(Int_str)); 
      istr->str = malloc(sizeof(char) * (strlen(buf) + 1));
      strcpy(istr->str, buf);
      istr->num = line;      
      queue_enqueue(queue, (FuncionCopia)int_str_return, istr);
    }    
  }
}

Queue spell_check(TablaHash dic, const char* path) {
  FILE* file = open_file(path, "r");
  Queue queue = queue_crear();

  char buf[50];
  char c;
  unsigned count = 0;
  unsigned line = 1;  
  while((c = fgetc(file)) != EOF) {
    c = tolower(c); 
    if('a' <= c && c <= 'z') {
      buf[count] = c;
      count++;
    } else {
      addToQueue(queue, dic, buf, count, line);
      count = 0;
    }   
    if(c == '\n')
      line++;
  }
  addToQueue(queue, dic, buf, count, line);
  fclose(file);
  return queue;
}

//TODO: borrar esta funcion, buscar sugerencia directamente en spell_check
void print_suggestions(TablaHash dictionary, const char* path) {
  Queue missp_words = spell_check(dictionary, path);
  Int_str* istr;
  while(!queue_vacia(missp_words)) {
    istr = queue_front(missp_words);
    printf("Linea %d, '%s' no esta en el diccionario.\n", istr->num, istr->str);
    create_suggestions(dictionary, istr->str);    
    queue_dequeue(missp_words, (FuncionDestructora)int_str_free);
  }
  queue_destruir(missp_words, (FuncionDestructora)int_str_free); 
}