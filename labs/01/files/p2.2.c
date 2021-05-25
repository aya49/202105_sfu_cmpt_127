// author: <First name, last name; YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: what does this program do?

#include <stdio.h>

int main(void) {
    // ADD COMMENT HERE
    float i = 0.0;
    float j = 1.0;
    float k = 2.0;
    
    // ADD COMMENT HERE
    printf("give me a number: \n");
    scanf("%f", &i);
    
    // ADD COMMENT HERE
    printf("the value of i is %.2f, its pointer points to address in memory %p\n", i, &i);
    printf("the value of j is %.1f, its pointer points to address in memory %p\n", j, &j);
    printf("the value of k is %.0f, its pointer points to address in memory %p\n", k, &k);
    
    return 0;
}
