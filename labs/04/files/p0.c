#include <stdio.h>
#include <stdlib.h>
#include "intarr.h"

// helper function that prints the content of the intarr
void print_intarr(intarr_t* ia) {
    if (ia == NULL) {
        printf("Invalid intarr (null).\n");
        return;
    }

    printf("Printing intarr of length %d:\n", ia->len);
    for (int i=0; i<ia->len; i++) {
        printf("%d ", ia->data[i]);
    }
    printf("\n");
}

int main() {
    // test variables to hold values returned by the functions
    intarr_t* test_ia = NULL;
    intarr_result_t test_result = INTARR_OK;


    // test practice 01 & 02
    printf("Creating test_ia by calling 'intarr_create(10)'\n");
    test_ia = intarr_create(10);
    if (test_ia == NULL) {
        printf("test_ia == NULL\n");
        return 1; //exit with a non-zero value
    }

    printf("Populating test_ia by calling 'intarr_set(test_ia, i, random)'\n");
    for (int i=0; i<test_ia->len; i++) {
        if(intarr_set(test_ia, i, (rand()%100)) != INTARR_OK) {
            printf("Cannot set value at index %d\n", i);
            return 1; //exit with a non-zero value
        }
    }

    printf("Printing test_ia\n");
    print_intarr(test_ia);

    printf("Getting a value from test_ia by calling 'intarr_get(test_ia, 0, val)'\n");
    int val = 100; //we know none of the values in test_ia is 100
    if (intarr_get(test_ia, 0, &val) != INTARR_OK) {
        printf("Cannot get value at index 0\n");
        return 1; //exit with a non-zero value
    } else {
        printf("Successfully got a value from test_ia: %d\n", val);
    }


    // test practice 03

    // test practice 04

    // test practice 05


    printf("Destroying test_ia\n");
    intarr_destroy(test_ia);

    return 0;
}
