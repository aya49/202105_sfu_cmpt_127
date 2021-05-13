#include "p3img.h"

int img_save_ppm(img_t* im, const char* filename) {
    // fopen file f
    fprintf(f, "P6\n%d %d\n255\n", im->cols, im->rows);

    static unsigned char color[3];
    // loop over rows i
        // loop over cols j
            // val = pixel value at row i col j 
            // - make sure val is greater or equal to 0 and less than or equal to 255.
            // - hint: one way to ensure this is to use % 255, look mod % up!
            
            color[0] = val;  /* red */
            color[1] = val;  /* green */
            color[2] = val;  /* blue */

            fwrite(color, 1, 3, f);

    // fclose file f
}