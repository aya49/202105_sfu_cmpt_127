#include <stdio.h>
#include <stdlib.h>
#include "p1intarr.h"

int intarr_save_binary( intarr_t* ia, const char* filename ) {
    if (ia == NULL || filename == NULL)
        return 4;

    FILE* f = fopen(filename, "w");

    if (f == NULL)       
        return 1;
    if (fwrite(&ia->len, sizeof(int), 1, f) != 1)
        return 2;
    if (fwrite(ia->data, sizeof(int), ia->len, f) != ia->len)
        return 3;

    fclose(f);
    return 0;
}

intarr_t* intarr_load_binary(const char* filename) {
    if (filename == NULL)
        return NULL;

    FILE* f = fopen(filename, "r");

    if (f == NULL)
        return NULL;

    intarr_t* ia = malloc(sizeof(intarr_t));
    if (ia == NULL)
        return NULL;
    if (fread(&ia->len, sizeof(int), 1, f) != 1)
        return NULL;
    
    ia->data = malloc(ia->len*sizeof(int));
    if (ia->data == NULL)
        return NULL;
    if (fread(ia->data, sizeof(int), ia->len, f) != ia->len)
        return NULL;
    
    fclose(f);
    return ia;
}