//TODO: crear .h
#include "spell_checker.h"
#include "IO.h"
#include "type_operations/inf_str.h"

void test_spell_check() {
  TablaHash dic = load_file("es1.txt", 1000000, 100);
  Pila pila = spell_check(dic, "texto.txt");
  pila_imprimir(pila, (FuncionVisitante)inf_str_visit);
  pila_destruir(pila, (FuncionDestructora)inf_str_free);
  tablahash_destruir(dic);  
}

int main() {
  test_spell_check();
}