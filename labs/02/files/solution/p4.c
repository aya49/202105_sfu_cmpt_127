// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 
// input: 
// output: 
// description: 

#include <stdio.h>
#include <string.h> // strlen

void contains(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // str1 cannot contain str2 if it is shorter than str2
    if (len1 < len2) {
        printf("false\n");
    }

    // try to see if you know what this loop does!
    int res = 1;
    for (int i=0; i<=len1-len2; i++) {
        for (int j=i; j<i+len2; j++) {
            res = 1;
            if (str1[j] != str2[j-i]) {
                res = 0;
                break;
            }
        }
        if (res==1) {
            printf("true\n");
            break;
        }
    }

    if (res!=1) {
        printf("false\n");
    }
}


int main(int argc, char* argv[]) {
    contains(argv[1], argv[2]);
    return 0;
}
