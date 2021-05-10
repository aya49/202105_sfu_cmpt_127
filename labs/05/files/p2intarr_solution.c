#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "intarr.h"

int intarr_save_json( intarr_t* ia, const char* filename ) {
    if (ia == NULL || filename == NULL)
        return 2;

    FILE* f = fopen(filename, "w");

    if (f == NULL)
        return 1;

    fprintf(f, "[");
    for (int i = 0; i < ia->len; i++) { 
        if (i == (ia->len -1)) {
            fprintf(f, " %d", ia->data[i]);
        } else {
            fprintf(f, " %d,", ia->data[i]);
        }
    }
    fprintf(f, " ]");

    fclose(f);
    return 0;
}

intarr_t* intarr_load_json( const char* filename ) {
    if (filename == NULL)
        return NULL;
    
    FILE* f = fopen(filename, "r");

    if (f == NULL)
        return NULL;

    intarr_t* new;
    new = intarr_create(0);
    if (new == NULL)
        return NULL;

    int len = 0;
    char current;
    char last ='0';
    
    while (!feof(f)) {
        current = getc(f);
        if (isdigit(current)) {
            if (!isdigit(last)) {
                len++;    
            }
        }
        last = current;
    }
    
    if (len == 0) {
        return new;
    }

    fseek(f, 0, SEEK_SET); 
    int data = 0;
    for (int i = 0; i < len; i++) {
        while(fscanf(f, "%d,", &data) != 1) {
            fseek(f, 1, SEEK_CUR);
        }
        intarr_push(new, data);
    }
    fseek(f, 0, SEEK_END);

    fclose(f);
    return new;
}