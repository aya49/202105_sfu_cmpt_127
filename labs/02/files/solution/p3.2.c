// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: 

#include <stdio.h> // getchar, EOF constant
#include <ctype.h> // isalpha

int main(void) {

    // initialize an array of floats
    // letters store the number of times each letter occurs in your file
    // e.g. letters[0] stores the number of times the letter 'a' occurs
    float letters[26] = {0};

    // count is the total number of letters in the file
    int count = 0;

    // initialize c with the first character in the file
    char c = getchar();

    // while we are not done reading the file
    while (c!= EOF) {

        // if c is an alphabet, we need to count it
        if (isalpha(c)) {

            // we increment the number of letters by 1
            count++;

            // if the letter is a capital letter, we convert it to lower case
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }

            // characters are integers
            // we convert c to an index we can use to index letters
            // e.g. 'a'-'a' = 0, 'c'-'a' = 2
            c -= 'a';

            // increment count of letter occurrence
            letters[c]++;
        }

        // get next character
        c = getchar();
    }

    // for each element in letter, normalize it (i.e. divide over count) and print it
    for (unsigned int i = 0; i < 26; i++) {
        if (letters[i] != 0) {
            printf("%c %.4f\n", 'a'+i, letters[i]/count);
        }
    }
    return 0;
}
