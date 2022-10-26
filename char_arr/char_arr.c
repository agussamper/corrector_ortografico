#include "char_arr.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct _Char_arr{
    char* str;
    unsigned size; // capacidad del arreglo
};

Char_arr char_arr_init(int size) {
    Char_arr arr = malloc(sizeof(struct _Char_arr));
    assert(arr);
    arr->str = malloc(sizeof(char) * size);
    assert(arr->str);
    arr->size = size;
    return arr;
}

void char_arr_destroy(Char_arr arr) {
    free(arr->str);
    free(arr);
}

void char_arr_write(Char_arr arr, unsigned pos, char ch) {
    if(pos < arr->size)
        arr->str[pos] = ch;
    else
        assert(NULL);
}

unsigned char_arr_size(Char_arr arr) {
    return arr->size;
}

void char_arr_resize(Char_arr arr, unsigned size) {
    arr->str = realloc(arr->str, sizeof(char) * size);
    assert(arr->str);
    arr->size = size;
}

char* char_arr_getStr(Char_arr arr) {
    return arr->str;
}