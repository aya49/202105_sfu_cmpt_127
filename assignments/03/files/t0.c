// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
#include <stdlib.h>
#include "p0img.h"

// helper function that prints the content of the img
void print_img(img_t* im) {
    if (im == NULL) {
        printf("Invalid img (null).\n");
        return;
    }

    printf("Printing img of length %d:\n", im->len);
    for (unsigned int i=0; i<im->row; i++) {
        for unsigned int j=0; j<im->col; j++) {
            printf("%d ", im->pixels[i][j]);
        }
    }
    printf("\n");
}

int main() {
    // test variables to hold values returned by the functions
    img_t* test_im = NULL;
    img_result_t test_result = IMG_OK;


    // test task 01 & 02
    printf("Creating test_im by calling 'img_create(10)'\n");
    test_im = img_create(10);
    if (test_im == NULL) {
        printf("test_im == NULL\n");
        return 1; //exit with a non-zero value
    }

    printf("Populating test_im by calling 'img_set(test_im, i, random)'\n");
    for (unsigned int i=0; i<test_im->row; i++) {
        for (unsigned int j=0; i<test_im->col; j++) {
            if (img_set(test_im, i, j, (rand()%100)) != IMG_OK) {
                printf("Cannot set value at index %d\n", i);
                return 1; //exit with a non-zero value
            }
        }
    }

    printf("Printing test_im\n");
    print_img(test_im);

    printf("Getting a value from test_im by calling 'img_get(test_im, 0, val)'\n");
    int val = 100; //we know none of the values in test_im is 100
    if (img_get(test_im, 0, 0, &val) != IMG_OK) {
        printf("Cannot get value at index 0\n");
        return 1; //exit with a non-zero value
    } else {
        printf("Successfully got a value from test_im: %d\n", val);
    }


    // test task 03

    // test task 04

    // test task 05


    printf("Destroying test_im\n");
    img_destroy(test_im);

    return 0;
}
