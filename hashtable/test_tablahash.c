#include "tablahash.h"
#include "contacto.h"
#include "assert.h"
#include "test_tablahash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TablaHash get_th_contactos(int sizeTable) {
  return tablahash_crear(
    sizeTable, (FuncionCopiadora)contacto_copia,
    (FuncionComparadora)contacto_comparar,
    (FuncionDestructora)contacto_destruir,
    (FuncionHash)contacto_heashear
  );
}

Contacto** get_contactos() {
  Contacto* contacto1 = contacto_crear("agus", "340524894", 20);
  Contacto* contacto2 = contacto_crear("ema", "34054564", 16);
  Contacto* contacto3 = contacto_crear("santi", "340554644", 18);
  Contacto* contacto4 = contacto_crear("dolo", "340521554", 25);
  Contacto* contacto5 = contacto_crear("zoe", "340524564", 30);
  Contacto* contacto6 = contacto_crear("juan", "340524564", 22);
  Contacto* contacto7 = contacto_crear("lucho", "34054594", 21);

  Contacto** contactos = malloc(sizeof(Contacto*) * 7);
  contactos[0] = contacto1;
  contactos[1] = contacto2;
  contactos[2] = contacto3;
  contactos[3] = contacto4;
  contactos[4] = contacto5;
  contactos[5] = contacto6;
  contactos[6] = contacto7;

  return contactos;
}

void test_tablahash() {
  TablaHash th = get_th_contactos(5);
  Contacto** contactos = get_contactos();
  for(int i = 0; i < 3; i++)
    tablahash_insertar(th, contactos[i]);

  assert(tablahash_nelems(th) == 3);
  assert(tablahash_capacidad(th) == 5);

  assert(tablahash_buscar(th, contactos[0]) != NULL);
  assert(tablahash_buscar(th, contactos[1]) != NULL);
  assert(tablahash_buscar(th, contactos[3]) == NULL);
  assert(tablahash_buscar(th, contactos[4]) == NULL); 

  tablahash_insertar(th, contactos[3]);
  assert(tablahash_nelems(th) == 4);
  assert(tablahash_capacidad(th) == 5);
  assert(tablahash_buscar(th, contactos[3]) != NULL); 

  tablahash_eliminar(th, contactos[3]);
  assert(tablahash_nelems(th) == 3);
  assert(tablahash_capacidad(th) == 5);

  printf("elems: %d\n", tablahash_nelems(th));
  for(int i = 3; i < 7; i++)
    tablahash_insertar(th, contactos[i]);
  for(int i = 0; i < 7; i++) {
    Contacto* cont = tablahash_buscar(th, contactos[i]);
    if(cont != NULL)
      contacto_imprimir(cont);
    puts("");
  }
  printf("elems: %d\n", tablahash_nelems(th));
  assert(tablahash_nelems(th) == 7);
  assert(tablahash_capacidad(th) == 10);

  // sobreescribiendo contacto
  Contacto* sobrew = contacto_crear("agus", "3402447319", 20);
  assert(strcmp(((Contacto*)tablahash_buscar(th ,contactos[0]))->tel, sobrew->tel) != 0);
  tablahash_insertar(th, sobrew);
  assert(strcmp(((Contacto*)tablahash_buscar(th, contactos[0]))->tel, sobrew->tel) == 0);
  contacto_destruir(sobrew);

  for(int i = 0; i < 7; i++)
    contacto_destruir(contactos[i]);
  free(contactos);

  tablahash_destruir(th);
}

int main() {
  test_tablahash();
  return 0;
}