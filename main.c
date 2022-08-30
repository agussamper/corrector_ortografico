#include<stdio.h>

#include "IO.h"
#include "spell_checker.h"

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("ARGUMENTOS:\n <RUTA> archivo de entrada\n <RUTA> archivo de salida\n");
    return 0;
  }
  const char* pathIn = argv[1];
  const char* pathOut = argv[2];
  
  TablaHash dic = load_file("dictionaries/es1.txt");
  spell_check(dic, pathIn, pathOut);

  tablahash_destruir(dic);  
  
  return 0;
}