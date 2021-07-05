#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Please add 2 strings to the argument\n");
        return 1;
    }

    char* str1 = argv[1];
    char* str2 = argv[2];

    int i = 0;
    int j = 0;

    // keep looping until I've reached the end of 
    // str1 or str2
    while (str1[i] != '\0' && str2[j] != '\0') {
        // move on to the next letter in str2 after
        // finding a match in str1
        if (str1[i] == str2[j]) {
            j++;
        }

        // move on to the next letter in str1
        i++;
    }

    // If I reached the end of the str2, then 
    // str2 occurs in str1
    if (str2[j] == '\0') {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}