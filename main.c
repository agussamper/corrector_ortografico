#include<stdio.h>

#include "IO.h"
#include "spell_checker.h"
#include <time.h> 

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
