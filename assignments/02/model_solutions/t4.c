#include <stdio.h>
#include <string.h>
#include <ctype.h>

void makeLowerCase(char* word) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        word[i] = tolower(word[i]);
    }
}

int compare(int stringLength, char* string, char* curWord, int* counter) {
    int length = strlen(curWord);

    // make sure the current word in the file is at least the length of 
    // the string that's being compared
    if (length >= stringLength) {
        for (int i = 0; i < length; i++) {
            /**
            strncmp only checks n bytes/chars of the string and returns 0 when equal
            
            curWord + i increments the pointer in the current word
            Example:
            string = "at"; // length 2
            curWord = "cat";
            
            i = 0;
            strncmp("at", curWord + 0 = "cat", 2); // checks "at" == "ca"
            i = 1;
            strncmp("at", curWord + 1 = "at", 2); // checks "at" == "at"
            **/
            if (strncmp(string, curWord + i, stringLength) == 0) { 
                // update the string's counter 
                *counter = *counter + 1;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    char* str1 = argv[1];
    char* str2 = argv[2];
    int str1len = strlen(str1);
    int str2len = strlen(str2);
    int c1 = 0;
    int c2 = 0;

    makeLowerCase(str1);
    makeLowerCase(str2);

    char lchar = getchar();
    char curWord[100] = {0};
    
    int letter = 0;
    
    while(lchar != EOF) {
        // strlen only works properly if there is \0 at the end
        // to signify the end of the string
        curWord[letter] = '\0';
        
        // reached the end of a word?
        if (lchar == ' ' || lchar == '\n') {
            letter = 0;
            makeLowerCase(curWord);
            
            // check if the 2 strings are a substring of the current word
            compare(str1len, str1, curWord, &c1);
            compare(str2len, str2, curWord, &c2);

        // keep building the word
        } else {
            curWord[letter] = lchar;
            letter++;
        }

        // get the next character in the file
        lchar = getchar();
    }

    printf("%s : %d\n", str1, c1);
    printf("%s : %d\n", str2, c2);

    return 0;
}
