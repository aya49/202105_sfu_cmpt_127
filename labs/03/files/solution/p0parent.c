// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
#include <stdlib.h>

void get_name(char line[], int maxlen) {
    printf("Please enter your name: ");

    // fgets reads at most maxlen-1 chars from stdin, up to first newline, 
    // EOF or error.
    if (fgets(line, maxlen, stdin) == 0) { // we ALWAYS check for I/O errors
        perror("failed to read a name");
        exit(1); // "break", but for the entire program
    }
}	

int main(void) {
    char name[1024]; // !! initializing name outside get_name fixes the bug !!
    get_name(name, 1024); // passes array pointer to get_name

    // we don't need to be lucky this time
    printf("Your name is %s", name);

    return 0;
}