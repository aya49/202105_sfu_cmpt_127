#include <stdio.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/
typedef struct { 
    uint8_t* pixels;
    unsigned int rows;
    unsigned int cols;
} img_t;


/* task 03 */

/*
  Save the entire 2D array im into a file called 'filename' in a .ppm
  text file image format. Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an empty output file.

  Make sure you validate the parameters before you use them.
*/
int img_save_ppm(img_t* im, const char* filename);