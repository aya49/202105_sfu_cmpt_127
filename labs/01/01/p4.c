// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: prints #'s for user inputs.
// this will NOT be graded.

#include <stdio.h>

int main(void) {
    // initialize while loop variable
    int j = 0;
    
    // promt for input
    printf("Enter integers separated by space and press enter:\n");
    
    // while the user does not end i.e. ctrl-d; print loop variable
    while (scanf("%d", &j) == 1) { // remember, 1 means true, 0 means false! True here meaning that scanf is still reading user inputs :)
        printf("%d", j);
    }
    return 0;
}