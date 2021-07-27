#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>

int main() {
    struct { 
        uint8_t* pixels;
        unsigned int cols;
        unsigned int rows;
    } img;
    
    img.cols = 640;
    img.rows = 480;
    uint8_t* a = malloc(img.rows * img.cols * sizeof(uint8_t));
    img.pixels = a;
    
    printf("%lu: size of unit8_t\n", sizeof(uint8_t*));
    printf("%lu: size of unsigned integer\n", sizeof(unsigned int));
    printf("%lu: size of unit8_t + (2 x unsigned integer)\n", sizeof(uint8_t*) + sizeof(unsigned int) + sizeof(unsigned int));
    printf("%lu: size of img\n\n", sizeof(img));
    
    printf("%lu: pointer to first element of 1D array pixels\n", a);
    printf("%lu: img.pixels\n", img.pixels);
    printf("%lu: img\n\n", img);
    
    printf("%lu: pointer to img.pixels\n", &img.pixels);
    printf("%lu: pointer to img\n\n", (void*)&img + 0);
    
    printf("%lu: pointer to img.cols\n", &img.cols);
    printf("%lu: pointer to img + sizeof(uint8_t*)\n\n", (void*)&img + sizeof(uint8_t*));
    
    printf("%lu: pointer to img.cols\n", &img.rows);
    printf("%lu: pointer to img + sizeof(uint8_t*) + sizeof(unsigned int)\n\n", (void*)&img + sizeof(uint8_t*) + sizeof(unsigned int));
    
    return 0;
}
