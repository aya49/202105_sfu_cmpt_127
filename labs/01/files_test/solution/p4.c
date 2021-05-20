// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: prints #'s for user inputs.

#include <stdio.h>

int main(void) {
    int j = 0;
    printf("Enter integers separated by space and press enter:\n");
    while (scanf("%d", &j) == 1) { // remember, 1 means true, 0 means false! True here meaning that scanf is still reading user inputs :)
        for (int i=0; i<j; i++) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}