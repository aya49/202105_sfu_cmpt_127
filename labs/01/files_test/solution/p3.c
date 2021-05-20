// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: prints non-100 values.

#include <stdio.h>

int main(void) {
    // for integers between 0 and 104
    for (int i=0; i<105; i++) {
        // if the integer is not 100, print it!
        if (i != 100) {
            printf("%d ", i++); // prints the value and THEN increments it 
        }
    }
    
    return 0;
}