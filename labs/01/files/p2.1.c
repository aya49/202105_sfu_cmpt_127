// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: takes an integer as input.

#include <stdio.h>

int main(void) {
    int i = 0; // 0 is just a placeholder value

    printf("Enter an integer: ");

    scanf("%d", &i); // scanf(<"type of input">, <the memory address, i.e. pointer, where scanf should put the input value into>)
    printf("Your integer was: %d\\n", i);

    return 0;
}