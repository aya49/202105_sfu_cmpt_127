// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#define _XOPEN_SOURCE        /* ALWAYS BEFORE the include statement */ 
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "p1imgr.h"


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
        printf("\n");
    }
    printf("\n");
}

int main() {
    // test variables to hold values returned by the functions
    img_t* test_im = NULL;
    img_result_t test_result = IMG_OK;


    // test task 01 & 02
    printf("Creating test_im by calling 'imgr_create(10, 10)'\n");
    test_im = img_create(10, 0);
    if (test_im == NULL) {
        printf("test_im == NULL\n");
        return 1; //exit with a non-zero value
    }

    printf("Populating test_im by calling 'imgr_set(test_im, i, j, random)'\n");
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


    // test task 02

    // test task 03


    printf("Destroying test_im\n");
    img_destroy(test_im);

    return 0;
}
