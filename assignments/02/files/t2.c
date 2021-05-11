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

    int a1[1] = {100};
    int a2[1] = {100};

    if (mirror(a1, a2, 1) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a1[7] = {5,2,2,3,4,5,5};
    int a2[7] = {5,5,4,3,2,2,5};

    if (mirror(a1, a2, 7) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    if (mirror(a1, a2, 0) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a1[2] = {1,1};
    int a2[2] = {1,2};

    if (mirror(a1, a2, 2) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a1[3] = {10,15,20};
    int a2[3] = {10,15,20};

    if (mirror(a1, a2, 3) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a1[5] = {1,2,3,4,5};
    int a2[5] = {5,3,4,1,2};

    if (mirror(a1, a2, 7) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    int a1[5] = {1,2,3,4,5};
    int a2[5] = {5,3,4,2,2};

    if (mirror(a1, a2, 7) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    return 0;
}
```