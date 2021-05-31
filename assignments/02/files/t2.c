// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
#include "t2mirror.h"

int main(void) {
    int a1[3] = {10, 15, 20};
    int a2[3] = {20, 15, 10};

    if (mirror(a1, a2, 3) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a3[1] = {100};
    int a4[1] = {100};

    if (mirror(a3, a4, 1) == 1) { 
        printf("a3 and a4 are mirrored\n");
    } else {
        printf("a3 and a4 are NOT mirrored\n");
    }

    int a5[7] = {5,2,2,3,4,5,5};
    int a6[7] = {5,5,4,3,2,2,5};

    if (mirror(a5, a6, 7) == 1) { 
        printf("a5 and a6 are mirrored\n");
    } else {
        printf("a5 and a6 are NOT mirrored\n");
    }

    if (mirror(a5, a6, 0) == 1) { 
        printf("a5 and a6 are mirrored\n");
    } else {
        printf("a5 and a6 are NOT mirrored\n");
    }

    int a7[2] = {1,1};
    int a8[2] = {1,2};

    if (mirror(a7, a8, 2) == 1) { 
        printf("a7 and a8 are mirrored\n");
    } else {
        printf("a7 and a8 are NOT mirrored\n");
    }

    int a9[3] = {10,15,20};
    int a10[3] = {10,15,20};

    if (mirror(a9, a10, 3) == 1) { 
        printf("a9 and a10 are mirrored\n");
    } else {
        printf("a9 and a10 are NOT mirrored\n");
    }

    int a11[5] = {1,2,3,4,5};
    int a12[5] = {5,3,4,1,2};

    if (mirror(a11, a12, 5) == 1) { 
        printf("a11 and a12 are mirrored\n");
    } else {
        printf("a11 and a12 are NOT mirrored\n");
    }

    int a13[5] = {1,2,3,4,5};
    int a14[5] = {5,3,4,2,2};

    if (mirror(a13, a14, 5) == 1) { 
        printf("a13 and a14 are mirrored\n");
    } else {
        printf("a13 and a14 are NOT mirrored\n");
    }

    return 0;
}
