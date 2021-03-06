// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
#include <stdlib.h>

char* get_name(void) {
    printf("Please enter your name: ");

    // should be enough space for a name
    char line[1024];
    
    // reads at most 1023 chars from stdin, up to first newline, 
    // EOF or error.
    if(fgets(line, 1024, stdin) == 0) {// we ALWAYS check for I/O errors
        perror("failed to read a name");
        exit(1);
    }
    
    return line; 
}

int main(void) {
    char* name = get_name();

    // works if we are *lucky*
    printf("Your name is %s\n", name);

    return 0;
}	             
