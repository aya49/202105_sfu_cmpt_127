#include "t3img.h"

int img_save_ppm(img_t* im, const char* filename) {
    // fopen file f
    fprintf(f, "T3\n%d %d\n255\n", im->cols, im->rows);

    static unsigned char color[3];
    //
    // USE THE COMMENTS BELOW TO HELP YOU WRITE YOUR CODE!
    // These are called "pseudocode" and are code written in english
    // writing pseudocode before starting to code is one strategy to help organize your thoughts!
    // Of course, you can write your own pseudocode too ;)
    //
    // loop over rows i
        // loop over cols j
            // val = pixel value at row i col j 
            // - make sure val is greater or equal to 0 and less than or equal to 255.
            // - hint: one way to ensure this is to use % 255, look mod % up!
            
            color[0] = val;  /* red */
            color[1] = val;  /* green */
            color[2] = val;  /* blue */

            write_to_file(color, 1, 3, f);

    // fclose file f
}