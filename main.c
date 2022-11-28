#include "IO.h"
#include "spell_checker.h"
#include <time.h> 
#include "char_arr/char_arr.h"
#include <ctype.h>

void aux_load_dic(TrieNode trie, Char_arr buf, unsigned* count) {
  if(*count > 0) {      
    char_arr_write(buf, *count, '\0');
    trie_insert(trie, char_arr_getStr(buf));
    *count = 0;        
  }      
}

/**
 * Recibe la ruta de un diccionario y carga todas sus palabras
 * en una estructura de tipo TrieNode, luego devuelve la
 * estructura.
 */
TrieNode load_dic(const char* path) {
  FILE* file = open_file(path, "r");
  TrieNode trie = trie_createNode();

  Char_arr buf = char_arr_init(100);
  char c;
  unsigned count = 0;
  while((c = fgetc(file)) != EOF) {
    c = tolower(c);
    if(('a' <= c) && (c <= 'z')) {
      if(count > char_arr_size(buf) - 2)
        char_arr_resize(buf, char_arr_size(buf)*2);
      char_arr_write(buf, count, c);
      count++;
    } else 
      aux_load_dic(trie, buf, &count);
  }
  aux_load_dic(trie, buf, &count);

  char_arr_destroy(buf);
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
