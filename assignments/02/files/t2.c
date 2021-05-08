// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
// FILL IN HERE: include header for t2mirror.c

int main(void) {
    int a1[3] = {10, 15, 20};
    int a2[3] = {10, 20, 15};

    if (mirror(a1, a2, 3) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    return 0;
}
```