# TP FINAL - Corrector ortográfico - Agustín Samper

## Decisión de estructura para guardar el diccionario.
Tuve en cuenta principalmente dos estructuras para guardar el diccionario, las cuales
son la tabla hash y un trie. 

### Razones por las que la tabla hash tiene un peor rendimiento a la hora de buscar en comparación con un trie
Con la implementación de tabla hash que se encuentra en el proyecto y
la función hash que usé str_KRHash que se encuentra en type_operations/strFunc.c
se generan colisiones al guardar un diccionario del tamaño del diccionario
de pruebas, por lo tanto el tiempo de busqueda no siempre es constante.
Además siempre que buscamos una palabra en el diccionario debemos llamar a la función hash.
La estructura trie no tiene colisiones ni tiene que calcular un hash siempre que se quiere
ver si una palabra está en el diccionario.
El tiempo de busqueda de una palabra en un trie es O(k) donde k es la longitud de la palabra.

### Desventaja de trie respecto a la tabla hash
La desventaja de trie respecto a la tabla hash es que ocupa más memoria que la tabla.
Esto es porque cada nodo del trie necesita al menos 26 * sizeof(pointer) + sizeof(char)
bytes por lo tanto generalmente requerirá más memoria que por ejemplo una tabla hash.
Aunque en el caso del diccionario podemos amortiguar un poco el gran requerimiento de
memoria ya que generalmente en los diccionarios muchas palabras comparten sufijos, 
por lo tanto, gran parte del espacio que requieran esas palabras sera compartido

### Conclusión
Elegí el trie para guardar el diccionario porque prioricé el tiempo de búsqueda sobre
el espacio, además muchas de las palabras tienen prefijos comunes lo que hace mucho del
espacio requerido por las palabras sea compartido.