// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
// FILL IN MERE: declaration of function implemented in identical.c

int identical(int i_array1[], int i_array2[], unsigned int len);

int main(void) {
    int a1[3] = {10, 15, 20};
    int a2[3] = {10, 20, 15};

    if (identical(a1, a2, 3) == 1) { 
        printf("a1 and a2 are identical\n");
    } else {
        printf("a1 and a2 are NOT identical\n");
    }

    return 0;
}