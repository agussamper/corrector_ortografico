# Corrector ortográfico

Corrector ortográfico hecho como trabajo práctico final de la materias Estructura de Datos y Algoritmos I. 

Este programa lee un archivo de diccionario, toma un archivo de texto de entrada y por cada error ortográfico encontrado el programa entrega una lista de sugerencias (si es que hay alguna).

El diccionario utilizado para generar las predicciones es el archivo es1.txt que se encuentra en la carpeta dictionaries.

## Modo de uso
Al compilar el programa con `makefile` se obtiene el ejecutable `program.out`, al cual para ejecutarlo debemos pasarle un archivo de entrada y de salida de la siguiente manera:
 ```bash
 > ./program.out archivoEntrada archivoSalida
```
Donde `archivoEntrada` es el archivo para el cual se van a buscar correcciones y `archivoSalida` es el archivo donde se van a guardar las correciones.
