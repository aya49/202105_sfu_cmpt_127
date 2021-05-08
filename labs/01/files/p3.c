// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: prints non-100 values.

#include <stdio.h>

int main(void) {
    for (int i=0; i<105; i++) {
        if (i == 100) {
            continue;
        }
        printf("%d ", i++); // prints the value and THEN increments it 
    }
    
    return 0;
}