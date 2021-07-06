// author: glory quan
// date: 2021-06-28
// input: 
// output: 
// description: this script tests the functions implemented in p0intarr.c

#include <stdio.h>
#include <stdlib.h>
#include "p0intarr.h"

// helper function that prints the content of the intarr
void print_intarr(intarr_t* ia) {
    if (ia == NULL) {
        printf("Invalid intarr (null).\n");
        return;
    }

    printf("Printing intarr of length %d:\n", ia->len);
    for (unsigned int i=0; i<ia->len; i++) {
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
    for (unsigned int i=0; i<test_ia->len; i++) {
        if (intarr_set(test_ia, i, (rand()%100)) != INTARR_OK) {
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
    intarr_t* test_ia_copy = intarr_copy(test_ia);
    if (test_ia_copy == NULL) {
        printf("malloc in intarr_copy failed.\n");
        return 1;
    }
    if (test_ia_copy->len != test_ia->len) {
        printf("test_ia_copy's len is different from test_ia's len.\n");
        return 1;
    }
    if (test_ia_copy->data == test_ia->data) {
        printf("Both data pointers in test_ia_copy and test_ia are the same\n");
        return 1;
    }
    for (int i = 0; i < test_ia->len; i++) {
        if (test_ia_copy->data[i] != test_ia->data[i]) {
            printf("Index %d in test_ia_copy has a different value than test_ia.\n", i);
            return 1;
        }
    }
    printf("Successfully created a deep copy of test_ia.\n");

    intarr_t* test_empty = intarr_create(5);
    intarr_t* test_empty_copy = intarr_copy(test_empty);
    if (test_empty_copy == NULL) {
        printf("malloc in intarr_copy failed.\n");
        return 1;
    }
    if (test_empty->len != test_empty_copy->len) {
        printf("test_ia_copy's len is different from test_ia's len.\n");
        return 1;
    }
    if (test_empty_copy->data == test_empty->data) {
        printf("Both data pointers in test_ia_copy and test_ia are the same\n");
        return 1;
    }
    for (int i = 0; i < test_empty->len; i++) {
        if (test_empty_copy->data[i] != test_empty->data[i]) {
            printf("Index %d in test_ia_copy has a different value than test_ia.\n", i);
            return 1;
        }
    }

    // test practice 04
    for(int i = 0; i < test_empty->len; i++) {
        intarr_set(test_empty, i, i);
    }
    int target = 3;
    int found;
    if (intarr_find(test_empty, target, &found) == INTARR_NOTFOUND) {
        printf("Could not find %d in test_empty.\n", target);
        return 1;
    }
    if (found != 3) {
        printf("Index %d for target %d in test_empty is incorrect.\n", found, target);
        return 1;
    }
    target = -1;
    if (intarr_find(test_empty, target, &found) == test_result) {
        printf("intarr_find return INTARR_OK for %d in test_empty.\n", target);
        return 1;
    }

    // test practice 05
    intarr_t* test_ia_subarray = intarr_copy_subarray(test_ia, 2, 8);
    if (test_ia_subarray->len != 7) {
        printf("Subarray's length does not equal 7\n");
        return 1;
    }
    for(int i = 0; i < test_ia_subarray->len; i++) {
        if (test_ia->data[i + 2] != test_ia_subarray->data[i]) {
            printf("Subarray at index %d does not equal test_ia's value.\n", i);
            return 1;
        }
    }
    intarr_t* test_ia_subarray2 = intarr_copy_subarray(test_ia, 2, 2);
    if (test_ia->data[2] != test_ia_subarray2->data[0]) {
        printf("Subarray2 does not equal test_ia's value at index 2.\n");
        return 1;
    }
    if (test_ia_subarray2->len != 1) {
        printf("Subarray2's length does not equal 1\n");
        return 1;
    }

    printf("Destroying test_ia\n");
    intarr_destroy(test_ia);

    printf("Destroying test_ia_copy\n");
    intarr_destroy(test_ia_copy);

    printf("Descripty type_empty\n");
    intarr_destroy(test_empty);

    printf("Destroying test_empty_copy\n");
    intarr_destroy(test_empty_copy);

    printf("Desctorying test_ia_subarray\n");
    intarr_destroy(test_ia_subarray);

    printf("Desctorying test_ia_subarray2\n");
    intarr_destroy(test_ia_subarray2);

    return 0;
}
