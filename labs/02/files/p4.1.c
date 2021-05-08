// author: <First name, last name; YOUR SFU USER ID HERE>
// date:
// input:
// output:
// description:

#include <stdio.h> // getchar, EOF constant
#include <ctype.h> // isalpha

// main() is the same as main(int argc, char* argv[])
// main(int argc, char* argv[]) is used so much that it was made the default!
int main() {
    // unsigned long int is a data type, search it up!
    unsigned long int charcount = 0;
    unsigned long int wordcount = 0; 
    unsigned long int linecount = 0;
    unsigned long int space = 0;

    // COMMENT HERE
    char last = getchar(); // getchar reads a character from stream, kind of like scanf
    
    // while not the end of file / ctrl-d
    while (last != EOF) { 
        // COMMENT HERE
        charcount++;

        // COMMENT HERE
        char current = getchar();

        // COMMENT HERE
        if (!isalpha(last) && isalpha(current)) { 
            wordcount++;
        }

        // COMMENT HERE
        if (current == '\n') {
            linecount++;
        }
        last = current;
    }
    printf("%lu %lu %lu\n", charcount, wordcount, linecount);

    return 0;
}