#include<stdio.h>

#include "IO.h"
#include "spell_checker.h"
#include <time.h> 

/**
 * Recibe la ruta de un diccionario y carga todas sus palabras
 * en una estructura de tipo TrieNode, luego devuelve la
 * estructura. Se supone que el archivo de texto en cada linea
 * solo tiene caracteres de la a a la z y las palabras están
 * en minúscula
 */
TrieNode load_dic(const char* path) {
  FILE* file = open_file(path, "r");
  int bufSize = 100;
  TrieNode trie = trie_createNode();
  char buf[bufSize];
  unsigned line = 0;
  while(fgets(buf, bufSize, file)) {
    size_t slen = strlen(buf);
    buf[--slen] = '\0'; //Resto 1 a slen por el '\n'
    trie_insert(trie, buf);
    line++;
  }
  fclose(file);
  return trie;
}

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("ARGUMENTOS:\n <RUTA> archivo de entrada\n <RUTA> archivo de salida\n");
    return 0;
  }
  const char* pathIn = argv[1];
  const char* pathOut = argv[2];
  
  clock_t t = clock();
  TrieNode dic = load_dic("dictionaries/es1.txt");
  spell_check(dic, pathIn, pathOut);  

  trie_destroy(dic);

  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  printf("The program took %f seconds to execute\n", time_taken);
  
  return 0;
}
