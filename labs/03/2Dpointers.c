#include <stdio.h>

int main(void) {
    int A[2][2];
    
    printf("\n");
    printf("\n");
    printf("%lu\n", &A[0][0]);
    printf("%lu\n", &A[0][1]);
    printf("%lu\n", &A[0][2]);
    
    printf("\n");
    printf("\n");
    printf("%lu\n", &A[1][0]);
    printf("%lu\n", &A[1][1]);
    printf("%lu\n", &A[1][2]);
    
    printf("\n");
    printf("\n");
    printf("%lu\n", &A[2][0]);
    printf("%lu\n", &A[2][1]);
    printf("%lu\n", &A[2][2]);
    
    return 0;
}
