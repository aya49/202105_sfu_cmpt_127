// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: 

#include <stdio.h> // getchar, EOF constant
#include <ctype.h> // isalpha

int main() {
    float letters[26] = {0};
    int count = 0;
    char c = getchar();

    while (c!= EOF) {
        if (isalpha(c)) {
            count++;
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
            c -= 'a';
            letters[c]++;
        }
        c = getchar();
    }
    for (unsigned int i = 0; i < sizeof(letters)/4; i++) {
        if (letters[i] != 0) {
            printf("%c %.4f\n", 'a'+i, letters[i]/count);
        }
    }
    return 0;
}
