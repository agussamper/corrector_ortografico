/**
 * carga el diccionario
 * 
 * usar una tabla hash para guardar el diccionario
 */
#include "IO.h"
#include "type_operations/strFunc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

FILE* open_file(const char* path, const char* mode) {
    FILE *file = fopen(path, mode);
    assert(file != NULL);
    return file;
}